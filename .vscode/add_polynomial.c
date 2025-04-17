/*
* 2025-1학기 자료구조 과제 1
* 과제명: 다항식 덧셈
* 학번: 2022041022
* 이름: 이정환
*/
//c언어 스타일
//이 코드는 다항식 덧셈을 구현한 코드입니다.

/////헤더파일
#define _CRT_SECURE_NO_WARNINGS//경고 무시 (visual_studio) 
#include<stdio.h>//기본 입출력 헤더파일
#include <malloc.h>//동적할당 헤더파일
#include <time.h>//시간측정 헤더파일



/////구조체 선언부
typedef struct binary_tree //다항식 이진트리 구조체(연결리스트로 구현)
{
	float coef;//계수
	int exp;//지수
	struct binary_tree* left;//왼쪽 자식 노드
	struct binary_tree* right;//오른쪽 자식 노드
}binary_tree;


typedef struct polynomial_2 //2번 배열 개선 자료구조
{
	float coef;//계수
	int exp;//지수
}polynomial_2;


typedef struct polynomial_3 //3번 연결리스트 자료구조
{
	float coef;//계수
	int exp;//지수
	struct polynomial_3* next;
}polynomial_3;



/////함수 선언부


//이진 트리 자료구조 함수
void tree_free(binary_tree*);//정렬된 이진트리 메모리 해제 함수 (후위순회 사용) //매개변수 이진트리의 루트주소
binary_tree* sort(FILE*);//파일에서의 다항식 받아 이를 이진트리로 정렬 //매개변수 input.txt파일 주소

//1번 자료구조 함수
void RVL_1(binary_tree*, float*, int*);//1번 자료구조를 만드는 함수(배열 자료구조)(중위순회 사용) //매개변수 이진트리의 루트주소, 1번 자료구조의 주소, 인덱스위치 값이 저장된 주소
float big_exp(binary_tree*);//가장 큰 지수를 찾는 함수(이진트리에서) //매개변수 이진트리의 루트주소
float small_exp(binary_tree*);//가장 작은 지수를 찾는 함수(이진트리에서) //매개변수 이진트리의 루트주소
void poly_1_fprint(float*, int);//1번 배열 자료구조 파일 프린트 함수 //매개변수 배열주소, 지수의 최소값
float* poly_add1(binary_tree*);//1번 배열 자료구조를 이용한 다항식 덧셈 출력 포함 //매개변수 이진트리의 루트주소

//2번 자료구조 함수
void RVL_2(binary_tree*, polynomial_2*, int*);//2번 자료구조를 만드는 함수(배열 개선 자료구조)(중위순회 사용) //매개변수 이진트리의 루트주소, 2번 자료구조의 주소, 인덱스위치 값이 저장된 주소
void poly_2_fprint(polynomial_2*,int,int);//2번 자료구조 파일 프린트함수 //매개변수 2번자료구조, 
polynomial_2* poly_add2(binary_tree*);//2번 배열 개선 자료구조를 이용한 다항식 덧셈 출력 포함 //매개변수 이진트리의 루트주소

//3번 자료구조 함수
void RVL_3(binary_tree*, polynomial_3**);//3번 자료구조를 만드는 함수(연결리스트 자료구조)(중위순회 사용)!!!!마지막에 빈노드가 추가되는 문제 있음 //매개변수 이진트리의 루트주소, 3번 자료구조의 헤드 주소
void last_node_pop(polynomial_3*);//연결리스트의 마지막 노드 삭제 함수 RVL_3의 문제 해결 방안 //3번 자료구조의 헤드 노드 주소
void linked_list_free(polynomial_3*);//3번 연결리스트 자료구조 메모리 해제 함수 //3번 자료구조의 헤드 노드 주소
void poly_3_fprint(polynomial_3**);// 3번 자료구조 파일 프린트 함수
polynomial_3* poly_add3(binary_tree*);//3번 연결리스트 자료구조를 이용한 다항식 덧셈 출력 포함 //매개변수 이진트리의 루트주소

//파일 입출력 함수
void outpu_time_file(clock_t[]);//출력 파일 쓰기 함수 (시간 측정 결과) //매개변수 각 계산 시간 배열

//기타 함수
void make_poly();//다항식 텍스트 파일 생성 함수



/////전역 변수
FILE* output;//출력 파일 포인터 편의를 위해 전역변수 선언



/////메인 함수
int main()
{
	//make_poly();//다항식 생성 함수 
	FILE* input;//입력 파일 포인터
	input = fopen("Input.txt", "r");//입력 파일 열기
	if (input == NULL)//오류처리 
	{
		return -1;
	}
	output = fopen("1.txt", "w");//출력 파일 열기
	if (output == NULL)//오류처리
	{
		return -1;
	}
	printf("1");
	clock_t start, end, time[4];//시간 측정용 배열
	start = clock();//시간 측정 시작
	binary_tree* head = sort(input);//정렬 함수
	end = clock();//시간 측정 종료
	time[0] = end - start;
	printf("2");
	start = clock();//시간 측정 시작
	float* poly_1 = poly_add1(head);//1번 배열 자료구조를 이용한 다항식 덧셈
	end = clock();//시간 측정 종료
	time[1] = end - start;
	printf("3");
	start = clock();//시간 측정 시작
	polynomial_2* poly_2 = poly_add2(head);//2번 배열 개선 자료구조를 이용한 다항식 덧셈
	end = clock();//시간 측정 종료
	time[2] = end - start;
	printf("4");
	start = clock();//시간 측정 시작
	polynomial_3* poly_3 = poly_add3(head);//3번 연결리스트 자료구조를 이용한 다항식 덧셈
	end = clock();//시간 측정 종료
	time[3] = end - start;
	/*디버깅용 코드
	printf("\n정렬된 이진트리의 시간: %f초\n", (float)time[0] / CLOCKS_PER_SEC);//시간 측정 결과 출력
	printf("1번 배열 자료구조를 이용한 다항식 덧셈의 시간: %f초\n", (float)time[1] / CLOCKS_PER_SEC);//시간 측정 결과 출력
	printf("2번 배열 개선 자료구조를 이용한 다항식 덧셈의 시간: %f초\n", (float)time[2] / CLOCKS_PER_SEC);//시간 측정 결과 출력
	printf("3번 연결리스트 자료구조를 이용한 다항식 덧셈의 시간: %f초\n", (float)time[3] / CLOCKS_PER_SEC);//시간 측정 결과 출력
	*/
	outpu_time_file(time);//출력 파일 쓰기 함수 호출

	fclose(input);//파일 닫기
	fclose(output);//파일 닫기
	tree_free(head);//정렬된 이진트리 메모리 해제
	free(poly_1);//1번 배열 자료구조 메모리 해제
	free(poly_2);//2번 배열 개선 자료구조 메모리 해제
	linked_list_free(poly_3);//3번 연결리스트 자료구조 메모리 해제
	return 0;//정상 종료
}



/////이하 함수 정의

//↓↓↓↓↓↓↓↓↓ 트리 정렬을 위한 함수
/*
* 자료구조
* 설명:
* 이진 트리를 이용한 트리 정렬
* 헤드 노드에 좌측 자식 노드에는 1번 다항식(head_1) 우측 자식 노드에는 2번 다항식(head_2)
* 헤드노드의 계수에는 1번 다항식의 항의 개수
* 헤드노드의 지수에는 2번 다항식의 항의 개수
*
* 이후 서브트리인 1번 다항식과(head_1) 2번 다항식(head_2)
* 지수가 높은 항은 오른쪽노드에 저장
* 지수가 낮은 항은 왼쪽노드에 저장
* 지수가 같으면 계수를 더하여 저장
* 의 방식으로 정렬
*
* 시공간복잡도:
* 공간 복잡도는 O(n+m) n='1번 다항식의 항의 개수', m='2번 다항식의 항의 개수'
* 이 자료구조를 이용한 아래 함수의 시간복잡도는 보통 O(nlog n) 최악 0(n^2) n='다항식의 항의 개수'
*/


void tree_free(binary_tree* node)
{
	if (node->left)//왼쪽 자식 노드 여부 확인
	{
		tree_free(node->left);//왼쪽 자식노드 재귀호출
	}
	if (node->right)//오른쪽 자식 노드 여부 확인
	{
		tree_free(node->right);//오른쪽 자식노드 재귀호출
	}
	free(node);//노드 메모리 해제
}


binary_tree* sort(FILE* input)
{
	binary_tree* head = NULL;//다항식두개를 저장하기 위한 이진트리의 헤드 노드
	head = (binary_tree*)calloc(1, sizeof(binary_tree));//이진트리의 헤드 노드 동적할당
	binary_tree* head_1 = NULL;//1번 다항식의 서브트리의 헤드 노드
	binary_tree* head_2 = NULL;//2번 다항식의 서브트리의 헤드 노드
	binary_tree* temp = NULL;//임시 노드(여기서는 만드려는 노드의 이전 즉 부모노드 뜻함)
	int coef, exp, num1, num2;//계수와 지수
	fscanf(input, "%d %d", &num1, &num2);//파일에서 두다항식의 항의 수를 읽어옴
	head->coef = num1;//헤드 노드의 계수에 1번 다항식의 항의 개수 저장
	head->exp = num2;//헤드 노드의 지수에 2번 다항식의 항의 개수 저장
	//이하 1번 다항식 저장
	if (num1 > 0)//num1이 0보다 크면 즉 다항식이 존재하면
	{
		fscanf(input, "%d %d", &coef, &exp);//파일에서 계수와 지수를 읽어옴
		head_1 = (binary_tree*)calloc(1, sizeof(binary_tree));//이진트리의 헤드 노드 동적할당
		head_1->coef = coef;//헤드 노드의 계수
		head_1->exp = exp;//헤드 노드의 지수

		for (int i = 1; i < num1; i++)//모든 항을 저장하기위한 반복문(이미 헤드노드에 하나의 항이 저장되었으니 1부터 시작) 
		{
			temp = head_1;//임시 노드에 헤드 노드 저장
			fscanf(input, "%d %d", &coef, &exp);//파일에서 계수와 지수를 읽어옴
			while (1)//새로운 노드 위치 찾을 고 생성할 때까지 반복
			{
				if (exp > temp->exp)//이전 노드(부모노드)의 함수가 현재 노드의 함수보다 크면
				{
					if (NULL == temp->right)//오른쪽 노드가 NULL이면
					{
						temp->right = (binary_tree*)calloc(1, sizeof(binary_tree));//오른쪽 노드 동적할당
						temp = temp->right;//임시 노드 변경
						temp->coef = coef;//노드의 계수 저장
						temp->exp = exp;//노드의 지수 저장
						break;//다음 항 받기
					}
					else//오른쪽 노드가 NULL이 아니면
					{
						temp = temp->right;//임시 노드 변경(레벨 내려가서 노드 위치 찾기)
						continue;//계속 반복
					}

				}
				else if (exp < temp->exp)//이전 노드(부모노드)의 함수가 현재 노드의 함수보다 작으면
				{
					if (NULL == temp->left)
					{
						temp->left = (binary_tree*)calloc(1, sizeof(binary_tree));//왼쪽 노드 동적할당
						temp = temp->left;//임시 노드 변경
						temp->coef = coef;//노드의 계수 저장
						temp->exp = exp;//노드의 지수 저장
						break;//다음 항 받기
					}
					else//왼쪽 노드가 NULL이 아니면
					{
						temp = temp->left;//임시 노드 변경(레벨 내려가서 노드 위치 찾기)
						continue;//계속 반복
					}
				}
				else if (exp == temp->exp)//지수가 같으면
				{
					temp->coef += coef;//계수를 더함
					head->coef--;//(1번 다항식의 항의 개수 감소)
					break;//다음 항 받기
				}
				else //지수가 같지도 크지도 작지도 않으면
				{
					exit(1);//종료
				}
			}
		}
		head->left = head_1;//헤드노드의 왼쪽 노드에 1번 다항식 저장
	}
	else
	{
		head->left = NULL;//헤드 노드에 다항식이 없으면 NULL로 설정
	}

	//이하 2번 다항식 저장(위 1번과 코드 거의 동일)
	if (num2 > 0)//num2이 0보다 크면 즉 다항식이 존재하면
	{
		fscanf(input, "%d %d", &coef, &exp);//파일에서 계수와 지수를 읽어옴
		head_2 = (binary_tree*)calloc(1, sizeof(binary_tree));//이진트리의 헤드 노드 동적할당
		head_2->coef = coef;//헤드 노드의 계수
		head_2->exp = exp;//헤드 노드의 지수
		for (int i = 1; i < num2; i++)//모든 항을 저장하기위한 반복문(이미 헤드노드에 하나의 항이 저장되었으니 1부터 시작) 
		{
			temp = head_2;//임시 노드에 헤드 노드 저장
			fscanf(input, "%d %d", &coef, &exp);//파일에서 계수와 지수를 읽어옴
			while (1)//새로운 노드 위치 찾을 고 생성할 때까지 반복
			{
				if (exp > temp->exp)//이전 노드(부모노드)의 함수가 현재 노드의 함수보다 크면
				{
					if (NULL == temp->right)//오른쪽 노드가 NULL이면
					{
						temp->right = (binary_tree*)calloc(1, sizeof(binary_tree));//오른쪽 노드 동적할당
						temp = temp->right;//임시 노드 변경
						temp->coef = coef;//노드의 계수 저장
						temp->exp = exp;//노드의 지수 저장
						break;//다음 항 받기
					}
					else//오른쪽 노드가 NULL이 아니면
					{
						temp = temp->right;//임시 노드 변경(레벨 내려가서 노드 위치 찾기)
						continue;//계속 반복
					}

				}
				else if (exp < temp->exp)//이전 노드(부모노드)의 함수가 현재 노드의 함수보다 작으면
				{
					if (NULL == temp->left)
					{
						temp->left = (binary_tree*)calloc(1, sizeof(binary_tree));//왼쪽 노드 동적할당
						temp = temp->left;//임시 노드 변경
						temp->coef = coef;//노드의 계수 저장
						temp->exp = exp;//노드의 지수 저장
						break;//다음 항 받기
					}
					else//왼쪽 노드가 NULL이 아니면
					{
						temp = temp->left;//임시 노드 변경(레벨 내려가서 노드 위치 찾기)
						continue;//계속 반복
					}
				}
				else if (exp == temp->exp)//지수가 같으면
				{
					temp->coef += coef;//계수를 더함
					head->exp--;//(2번 다항식의 항의 개수 감소)
					break;//다음 항 받기
				}
				else //지수가 같지도 크지도 작지도 않으면
				{
					exit(2);//종료
				}
			}
		}
		head->right = head_2;//헤드노드의 오른쪽 노드에 2번 다항식 저장
	}
	else
	{
		head->left = NULL;//헤드 노드에 다항식이 없으면 NULL로 설정
	}

	return head;//헤드 노드 반환
}


//↑↑↑↑↑↑↑↑↑ 이진트리를 위한 함수

//↓↓↓↓↓↓↓↓↓ 1 번자료구조를 위한 함수
/*
* 자료구조
* 설명:
* 단순 배열
* poly[0]='가장 큰 지수'
* polynomial_1[i].coef='(polynomial_1[0]-i)라는 지수를 가지는 항의 계수'
*
* 시공간 복잡도:
* 배열의 사이즈는('가장 큰 지수+2')byte							+2->(2byte 최고 지수 저장용 1byte 지수가 0인 계수 1byte)
* 즉 공간 복잡도 O(n) n='가장 큰 지수'
* 이 자료구조를 이용한 아래 함수의 시간복잡도의 경우는 O(n) n='가장 큰 지수'
*
*
* 추가로
* 기존의 배열형식의 자료구조만 사용했음
* 각종 비효율 함수를 제거해서(ex:remove 함수) 시간복잡도상으로는 기존의 방식보다는 빠르게 동작함
*/


void RVL_1(binary_tree* node, float* coe, int* i)
{
	if (node->right)//오른쪽 자식 노드 여부 확인
	{
		RVL_1(node->right, coe, i);//오른쪽 자식노드 재귀호출
	}
	coe[(int)(*coe) + 1 - node->exp] = node->coef;//계수 저장 //배열의 길이 - 현재 항의 계수 -1 =1번 자료구조의 계수의 인덱스 위치
	if (node->left)
	{
		RVL_1(node->left, coe, i);//왼쪽 자식노드 재귀호출
	}
	else if (*i > coe[0])
	{
		exit(3);//종료
	}
}


float big_exp(binary_tree* tree)
{
	if (tree->right)
	{
		return big_exp(tree->right);//재귀호출후	가장 큰 지수 반환

	}
	else
	{
		return tree->exp;//가장 큰 지수 반환
	}
}


float small_exp(binary_tree* tree)
{
	if (tree->left)
	{
		return small_exp(tree->left);//재귀호출후	가장 작은 지수 반환
	}
	else
	{
		return tree->exp;//가장 작은 지수 반환
	}
}

void poly_1_fprint(float* poly, int small)
{
	for (int i = 1; i < poly[0] + 2; i++)//결과 다항식 출력
	{
		if (poly[i] != 0)//계수가 0이 아니면 즉 함수의 끝이 아니면
		{
			fprintf(output, "%0.fx^%d", poly[i], (int)(poly[0] - i + 1));//결과 다항식의 계수 출력
			if ((int)(poly[0] - i + 1) != small)//가장 작은 지수와 같지 않으면 즉 식의 끝이 아니면
			{
				fprintf(output, " + ");//계수와 계수 사이에 + 출력
			}
			//디버깅용 코드
			/*
			printf("%0.fx^%d", poly[i], (int)(poly[0] - i + 1));//결과 다항식의 계수 출력
			if (int)(poly[0] - i + 1) != small)//가장 작은 지수와 같지 않으면 즉 식의 끝이 아니면
			{
				printf("+");//계수와 계수 사이에 + 출력
			}
			*/
		}
	}
	//printf("\n");//디버깅용 코드
	fprintf(output, "\n");
}
float* poly_add1(binary_tree* head)
{
	float* poly_a = NULL;//1번 다항식의 포인터
	float* poly_b = NULL;//2번 다항식의 포인터
	float* poly_d = NULL;//결과 다항식의 포인터
	int iii = big_exp(head->left);//1번 다항식의 가장큰 지수
	poly_a = (float*)calloc(iii + 2, sizeof(float));//1번 다항식 동적할당
	poly_a[0] = iii;
	iii = big_exp(head->right);//2번 다항식의 가장큰지수
	poly_b = (float*)calloc(iii + 2, sizeof(float));//2번 다항식 동적할당
	poly_b[0] = iii;
	iii = 0;
	RVL_1(head->left, poly_a, &iii);//1번 다항식의 계수를 배열에 저장
	iii = 0;
	RVL_1(head->right, poly_b, &iii);//2번 다항식의 계수를 배열에 저장
	float* max_poly = poly_a[0] >= poly_b[0] ? poly_a : poly_b;//큰 지수를 가지는 다항식
	float* min_poly = poly_a[0] < poly_b[0] ? poly_a : poly_b;//작은 지수를 가지는 다항식
	poly_d = (float*)calloc((max_poly[0] + 2), sizeof(float));//결과 다항식 동적할당
	poly_d[0] = max_poly[0];//결과 다항식의에 가장 큰 지수 저장
	int i = 1;//반복문을 위한 변수(배열의 0번째 위치는 이미 값이 저장되어 있으니 1부터 시작)
	for (; i < ((int)(poly_d[0] - min_poly[0]) + 1); i++)//큰 지수의 다항식의 계수부터 합하기 시작
	{
		poly_d[i] = max_poly[i];//결과 다항식의 계수에 큰 지수의 계수 저장
	}
	for (int ii = 1; ii < ((int)(min_poly[0]) + 2); i++, ii++)
	{
		poly_d[i] = max_poly[i] + min_poly[ii];//결과 다항식의 계수에 큰 지수의 남은 계수와 작은 지수의 계수 저장
	}
	//1번식 파일 출력
	poly_1_fprint(poly_a, small_exp(head->left));
	//2번식 파일 출력
	poly_1_fprint(poly_b, small_exp(head->right));
	//결과 다항식 파일 출력
	int small = small_exp(head->left) < small_exp(head->right) ? small_exp(head->left) : small_exp(head->right);//가장 작은 지수
	poly_1_fprint(poly_d, small);
	free(poly_a);//1번 다항식 메모리 해제
	free(poly_b);//2번 다항식 메모리 해제
	return poly_d;//결과 다항식 반환
}


//↑↑↑↑↑↑↑↑↑ 1 번자료구조를 위한 함수

//↓↓↓↓↓↓↓↓↓ 2 번자료구조를 위한 함수
/*
*
* 자료구조
* 설명:
* 실수와 정수로 이루어진 2중배열
* poly[i].coef='계수' poly[i].exp='지수' (i<'1번 항과 2번항의 개수의 합')
*
* 시공간 복잡도:
*  배열의 사이즈는('총 항의수')*2byte = ('1번 항과 2번항의 개수의 합')*(1byte 1+byrte '계수'+'지수') = 2n
* 즉 공간 복잡도는 O(n) n='1번 항과 2번항의 개수의 합'
* 즉 시간간복잡도는 O(n) n='1번 항과 2번항의 개수의 합'
*
*
* 추가로
* 기존의 배열형식의 자료구조만 사용했음
*/


void RVL_2(binary_tree* node, polynomial_2* poly, int* i)
{
	if (node->right)//오른쪽 자식 노드 여부 확인
	{
		RVL_2(node->right, poly, i);//오른쪽 자식노드 재귀호출
	}
	poly[*i].coef = node->coef;//계수 저장
	poly[*i].exp = node->exp;//지수 저장
	(*i)++;//다음 배열로 이동
	if (node->left)
	{
		RVL_2(node->left, poly, i);//왼쪽 자식노드 재귀호출
	}
}

void poly_2_fprint(polynomial_2* poly,int ii,int i)
{
	for (; i < ii; i++)//결과 다항식 출력
	{
		if (poly[i].coef != 0)//계수가 0이 아니면 즉 함수의 끝이 아니면
		{
			fprintf(output, "%0.fx^%d", poly[i].coef, poly[i].exp);//결과 다항식의 계수 출력
			if (i < ii - 1)//마지막 항이 아니면
			{
				fprintf(output, " + ");
			}
			//디버깅용 코드
			/*
			printf("%0.fx^%d", poly[i].coef, poly[i].exp);//결과 다항식의 계수 출력
			if (i < ii - 1)//마지막 항이 아니면
			{
				printf("+");
			}
			*/
			}
	}
	fprintf(output, "\n");
}

polynomial_2* poly_add2(binary_tree* head)
{
	polynomial_2* poly_a = NULL;//다항식의 포인터
	polynomial_2* poly_d = NULL;//결과 다항식의 포인터
	int j = 0;// RVL_2함수에서 몇번째 항인지 확인하기 위한 변수
	poly_a = (polynomial_2*)calloc(head->coef + head->exp, sizeof(polynomial_2));//다항식 동적할당
	RVL_2(head->left, poly_a, &j);//1번 다항식의 계수를 개선 배열에 저장
	RVL_2(head->right, poly_a, &j);//2번 다항식의 계수를 개선 배열에 저장
	poly_d = (polynomial_2*)calloc(head->coef + head->exp, sizeof(polynomial_2));//결과 다항식 동적할당 최악의 경우를 상정하여 두항의 합의 개수로 동적할당
	int ii = 0, iii = 0;//계산을 위한 변수
	j = 0;//다시 초기화
	for (int i = 0, ii = 0, iii = 0; 1; i++)//두 다항식의 합
	{
		if (ii >= head->coef)//1번 다항식의 항의 개수를 초과하면
		{
			for (; iii < head->exp; i++, iii++)
			{
				poly_d[i].coef = poly_a[iii + (int)(head->coef)].coef;//계수 저장
				poly_d[i].exp = poly_a[iii + (int)(head->coef)].exp;//지수 저장
			}
			break;//반복문 종료
		}
		else if (iii >= head->exp)//2번 다항식의 항의 개수를 초과하면
		{
			for (; ii < head->coef; i++, ii++)
			{
				poly_d[i].coef = poly_a[ii].coef;//계수 저장
				poly_d[i].exp = poly_a[ii].exp;//지수 저장
			}
			break;//반복문 종료
		}
		if (poly_a[ii].exp == poly_a[iii + (int)(head->coef)].exp)//지수가 같으면
		{
			poly_d[i].coef = poly_a[ii].coef + poly_a[iii + (int)(head->coef)].coef;//계수를 더함
			poly_d[i].exp = poly_a[ii].exp;//지수 저장
			ii++;//1번 다항식 다음 배열로 이동
			iii++;//2번 다항식 다음 배열로 이동
			j++;//사이즈 감소
			continue;//계속 반복
		}
		else if (poly_a[ii].exp > poly_a[iii + (int)(head->coef)].exp)//1번 다항식의 지수가 더 크면
		{
			poly_d[i].coef = poly_a[ii].coef;//계수 저장
			poly_d[i].exp = poly_a[ii].exp;//지수 저장
			ii++;//1번 다항식 다음 배열로 이동
			continue;//계속 반복
		}
		else//2번 다항식의 지수가 더 크면
		{
			poly_d[i].coef = poly_a[iii + (int)(head->coef)].coef;//계수 저장
			poly_d[i].exp = poly_a[iii + (int)(head->coef)].exp;//지수 저장
			iii++;//2번 다항식 다음 배열로 이동
			continue;//계속 반복
		}
	}
	poly_d = (polynomial_2*)realloc(poly_d, sizeof(polynomial_2) * ((int)(head->coef)+ head->exp - j));//결과 다항식 동적할당 최악의 경우를 상정하여 두항의 합의 개수로 동적할당
	//1번식 파일 출력
	poly_2_fprint(poly_a, (int)(head->coef),0);
	//2번식 파일 출력
	poly_2_fprint(poly_a, ((int)(head->coef) + head->exp), (int)(head->coef));
	//결과 다항식 파일 출력
	poly_2_fprint(poly_d, ((int)(head->coef) + head->exp - j),0);;
	free(poly_a);//다항식 메모리 해제
	return poly_d;//결과 다항식 반환
}


//↑↑↑↑↑↑↑↑↑ 2 번자료구조를 위한 함수

//↓↓↓↓↓↓↓↓↓ 3 번자료구조를 위한 함수
/*
*
* 자료구조
* 설명:
* 실수와 정수로 이루어진 연결리스트
* poly->next='다음 노드' poly->coef='계수' poly->exp='지수'
*
* 시공간 복잡도:
* 링크드 리스트의 사이즈는 ('총 항의수')*3byte = ('총 항의 개수의 합')*( '계수'+'지수','포인터') = 3n
* 즉 공간 복잡도는 O(n) n='총항의 개수의 합'
* 이 자료구조를 이용한 아래 함수의 시간복잡의 경우는
* O(n) n ='1번다항식 노드 수 + 2번 다항식 노드의 수'
*
*
* 추가로
* 기존의 연결리스트 자료구조만 사용했음
*/


void RVL_3(binary_tree* node, polynomial_3** temp)
{
	if (node->right)//오른쪽 자식 노드 여부 확인
	{
		RVL_3(node->right, temp);//오른쪽 자식노드 재귀호출
	}
	(*temp)->coef = node->coef;
	(*temp)->exp = node->exp;
	(*temp)->next = (polynomial_3*)calloc(1, sizeof(polynomial_3));//다음 노드 동적할당
	(*temp) = (*temp)->next;
	if (node->left)
	{
		RVL_3(node->left, temp);//왼쪽 자식노드 재귀호출
	}
}



void linked_list_free(polynomial_3* poly)
{
	polynomial_3* temp = NULL;//임시 노드 포인터
	while (poly != NULL)//노드의 끝까지 반복
	{
		temp = poly;//임시 노드에 현재 노드 저장
		poly = poly->next;//현재 노드를 다음 노드로 설정
		free(temp);//임시 노드 메모리 해제
	}
	free(poly);//마지막 노드 메모리 해제
}


void last_node_pop(polynomial_3* head)
{
	if (head->next == NULL) // 헤드노드 만 있는 경우
	{
		free(head);
		head = NULL;
		return;
	}

	// 마지막 노드 이전 노드를 찾기 위해 탐색
	polynomial_3* temp = head;
	while (temp->next->next != NULL) // 마지막 노드 이전 노드까지 탐색
	{
		temp = temp->next;
	}
	free(temp->next);// 마지막 노드 삭제
	temp->next = NULL; // 마지막 노드 이전 노드의 next를 NULL로 설정
}

void poly_3_fprint(polynomial_3* head)
{
	for (polynomial_3* temp = head; temp != NULL; temp = temp->next)//결과 다항식 출력
	{
		fprintf(output, "%0.fx^%d", temp->coef, temp->exp);//결과 다항식의 계수 출력
		if (temp->next != NULL)//마지막 항이 아니면
		{
			fprintf(output, " + ");
		}
		//디버깅용 코드
		/*
		printf("%0.fx^%d", temp->coef, temp->exp);//결과 다항식의 계수 출력
		if (temp->next != NULL)//마지막 항이 아니면
		{
			printf("+");
		}
		*/
	}
	//printf("\n");//디버깅용 코드
	fprintf(output, "\n");
}

polynomial_3* poly_add3(binary_tree* head)
{
	polynomial_3* poly_a_head = NULL;//1번 다항식의 포인터
	polynomial_3* poly_b_head = NULL;//2번 다항식의 포인터
	polynomial_3* poly_d_head = NULL;//결과 다항식의 포인터
	polynomial_3* poly_a = NULL;//1번 다항식 임시 포인터
	polynomial_3* poly_b = NULL;//2번 다항식 임시 포인터
	polynomial_3* poly_d = NULL;//결과 다항식의 임시 포인터
	polynomial_3** temp = NULL;//임시 2중 포인터
	poly_a_head = (polynomial_3*)calloc(1, sizeof(polynomial_3));//1번 다항식 동적할당
	poly_b_head = (polynomial_3*)calloc(1, sizeof(polynomial_3));//2번 다항식 동적할당
	poly_d_head = (polynomial_3*)calloc(1, sizeof(polynomial_3));//결과 다항식 동적할당
	poly_a = poly_a_head;//1번 다항식의 포인터
	poly_b = poly_b_head;//2번 다항식의 포인터
	temp = &poly_a;
	RVL_3(head->left, temp);// 1번 다항식의 계수를 연결리스트에 저장
	temp = &poly_b;
	RVL_3(head->right, temp);//2번 다항식의 계수를 연결리스트에 저장
	last_node_pop(poly_a_head);//1번 다항식의 마지막 노드 삭제
	last_node_pop(poly_b_head);//2번 다항식의 마지막 노드 삭제
	poly_a = poly_a_head;//1번 다항식의 포인터
	poly_b = poly_b_head;//2번 다항식의 포인터
	poly_d = poly_d_head;//결과 다항식의 포인터
	for (; 1;)//두 다항식의 합
	{
		if (poly_a == NULL)//1번 다항식의 끝에 도달하면
		{
			for (; poly_b != NULL; poly_b = poly_b->next)//2번 다항식의 남은 항을 결과 다항식에 저장
			{
				poly_d->coef = poly_b->coef;//계수 저장
				poly_d->exp = poly_b->exp;//지수 저장
				poly_d->next = (polynomial_3*)calloc(1, sizeof(polynomial_3));//결과 다항식 다음 노드 동적할당
				poly_d = poly_d->next;//결과 다항식 다음 노드로 이동
			}
			break;//반복문 종료
		}
		else if (poly_b == NULL)//2번 다항식의 끝에 도달하면
		{
			for (; poly_a != NULL; poly_a = poly_a->next)//1번 다항식의 남은 항을 결과 다항식에 저장
			{
				poly_d->coef = poly_a->coef;//계수 저장
				poly_d->exp = poly_a->exp;//지수 저장
				poly_d->next = (polynomial_3*)calloc(1, sizeof(polynomial_3));//결과 다항식 다음 노드 동적할당
				poly_d = poly_d->next;//결과 다항식 다음 노드로 이동
			}
			break;//반복문 종료
		}
		else if (poly_a->exp == poly_b->exp)//계수가 같으면
		{
			poly_d->coef = poly_a->coef + poly_b->coef;//계수를 더함
			poly_d->exp = poly_a->exp;//지수 저장
			poly_a = poly_a->next;//1번 다항식 다음 노드로 이동
			poly_b = poly_b->next;//2번 다항식 다음 노드로 이동
			poly_d->next = (polynomial_3*)calloc(1, sizeof(polynomial_3));//결과 다항식 다음 노드 동적할당
			poly_d = poly_d->next;//결과 다항식 다음 노드로 이동
			continue;//계속 반복
		}
		else if (poly_a->exp > poly_b->exp)//1번 다항식의 지수가 더 크면
		{
			poly_d->coef = poly_a->coef;//계수 저장
			poly_d->exp = poly_a->exp;//지수 저장
			poly_a = poly_a->next;//1번 다항식 다음 노드로 이동
			poly_d->next = (polynomial_3*)calloc(1, sizeof(polynomial_3));//결과 다항식 다음 노드 동적할당
			poly_d = poly_d->next;//결과 다항식 다음 노드로 이동
			continue;//계속 반복
		}
		else //2번 다항식의 지수가 더 크면
		{
			poly_d->coef = poly_b->coef;//계수 저장
			poly_d->exp = poly_b->exp;//지수 저장
			poly_b = poly_b->next;//2번 다항식 다음 노드로 이동
			poly_d->next = (polynomial_3*)calloc(1, sizeof(polynomial_3));//결과 다항식 다음 노드 동적할당
			poly_d = poly_d->next;//결과 다항식 다음 노드로 이동
			continue;//계속 반복
		}
	}
	last_node_pop(poly_d_head);//결과 다항식의 마지막 노드 삭제
	poly_3_fprint(poly_a_head);//1번 다항식 출력
	poly_3_fprint(poly_b_head);//2번 다항식 출력
	poly_3_fprint(poly_d_head);//3번 다항식 출력
	linked_list_free(poly_a_head);//1번 다항식 메모리 해제
	linked_list_free(poly_b_head);//2번 다항식 메모리 해제
	return poly_d_head;//결과 다항식 반환
}


//↑↑↑↑↑↑↑↑↑↑↑3번 자료구조를 위한 함수


void outpu_time_file(clock_t time[4])
{
	//시간 측정 결과 출력
	//fprintf(ouput, "%0.4f\t", (float)time[0] / CLOCKS_PER_SEC);//트리정렬 시간 측정 결과 출력
	fprintf(output, "%0.4f\t", (float)(time[1]) / CLOCKS_PER_SEC);//1번 자료구조 시간 측정 결과 출력
	fprintf(output, "%0.4f\t", (float)(time[2]) / CLOCKS_PER_SEC);//2번 자료구조 시간 측정 결과 출력
	fprintf(output, "%0.4f\n", (float)(time[3]) / CLOCKS_PER_SEC);//3번 자료구조 시간 측정 결과 출력
}


//편의를 위한 함수
void make_poly()
{
	FILE* file = fopen("Input.txt", "w");
	if (file == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
	}

	int i = 2;//1번 다항식의 항의 개수
	int ii = 3;//2번 다항식의 항의 개수
	int iii = 5;//계수의 범위
	int iV = 4;//지수의 범위
	fprintf(file, "%d %d\n", i, ii);
	iV += 1;//0포함
	srand(time(NULL)); // 랜덤 시드 설정

	for (int j = 0; j < (i + ii); j++)
	{ // i+j 줄 생성
		int num1 = (rand() % iii + 1); // 첫 번째 숫자 범위
		int num2 = (rand() % iV + 1) - 1; // 두 번째 숫자 범위
		fprintf(file, "%d %d\n", num1, num2);
	}

	fclose(file);
	printf("파일 생성 완료\n");
}
