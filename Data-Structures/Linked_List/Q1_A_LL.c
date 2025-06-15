//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
    int item;               // item 이라는 int 자료형 값을 가짐
    struct _listnode *next; // ListNode 라는 타입을 가진 구조체의 주소를 가짐
} ListNode;                 // You should not change the definition of ListNode

typedef struct _linkedlist
{
    int size;       // size 라는 값을 가져요.
    ListNode *head; // 별칭 ListNode 타입을 가지는 *head 라는 이름의 주소예요.
} LinkedList;       // You should not change the definition of LinkedList

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
    LinkedList ll;
    int c, i, j;
    c = 1;

    // Initialize the linked list 1 as an empty linked list
    ll.head = NULL;
    ll.size = 0;

    printf("1: Insert an integer to the sorted linked list:\n");
    printf("2: Print the index of the most recent input value:\n");
    printf("3: Print sorted linked list:\n");
    printf("0: Quit:");

    while (c != 0)
    {
        printf("\nPlease input your choice(1/2/3/0): ");
        scanf("%d", &c);

        switch (c)
        {
        case 1:
            printf("Input an integer that you want to add to the linked list: ");
            scanf("%d", &i);
            j = insertSortedLL(&ll, i);
            printf("The resulting linked list is: ");
            printList(&ll);
            break;
        case 2:
            printf("The value %d was added at index %d\n", i, j);
            break;
        case 3:
            printf("The resulting sorted linked list is: ");
            printList(&ll);
            removeAllItems(&ll);
            break;
        case 0:
            removeAllItems(&ll);
            break;
        default:
            printf("Choice unknown;\n");
            break;
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

/*
 * insertSortedLL 은 정수를 입력해서 오름차순으로 정렬된 연결리스트를 유지해요.
 * 정수가 현재 목록에 있는 경우는 삽입하지 않아요. return -1
 * 함수가 성공적으로 완료되지 않으면( 값이 추가되지 않으면 ) return -1
 * 새 항목이 추가되면 해당 인덱스를 반환해요.  return index
 */
int insertSortedLL(LinkedList *ll, int item)
{
    ListNode *current = ll->head;
    int index = 0;
    
    // 연결리스트의 head 노드가 비어있거나 head 보다 작은 값이 들어온 경우 바로 넣어줍니다.
    if (ll->head == NULL || ll->head->item > item)
        return insertNode(ll, index, item);

    // 그 외의 경우 알맞은 index 위치를 찾아줍니다.
    do {
        int value = current->item;

        if (value == item) return -1;
        if (value > item) break;
        if (value < item)   {
            current = current->next;
            index++;
        }
    } while (current != NULL);

    // 정상적으로 값이 입력되지 않은 경우는 -1 을 return 합니다. 성공적이면 index 를 return 합니다.
    if (insertNode(ll, index, item) == 0) {
        return index;
    } else {
        return -1;
    }
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll)
{

    ListNode *cur;
    if (ll == NULL)
        return;
    cur = ll->head;

    if (cur == NULL)
        printf("Empty");
    while (cur != NULL)
    {
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

void removeAllItems(LinkedList *ll)
{
    ListNode *cur = ll->head;
    ListNode *tmp;

    while (cur != NULL)
    {
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    ll->head = NULL;
    ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index)
{

    ListNode *temp;

    if (ll == NULL || index < 0 || index >= ll->size)
        return NULL;

    temp = ll->head;

    if (temp == NULL || index < 0)
        return NULL;

    while (index > 0)
    {
        temp = temp->next;
        if (temp == NULL)
            return NULL;
        index--;
    }

    return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{

    ListNode *pre, *cur;

    if (ll == NULL || index < 0 || index > ll->size + 1)
        return -1;

    // If empty list or inserting first node, need to update head pointer
    if (ll->head == NULL || index == 0)
    {
        cur = ll->head;
        ll->head = malloc(sizeof(ListNode));
        ll->head->item = value;
        ll->head->next = cur;
        ll->size++;
        return 0;
    }

    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    if ((pre = findNode(ll, index - 1)) != NULL)
    {
        cur = pre->next;
        pre->next = malloc(sizeof(ListNode));
        pre->next->item = value;
        pre->next->next = cur;
        ll->size++;
        return 0;
    }

    return -1;
}

int removeNode(LinkedList *ll, int index)
{

    ListNode *pre, *cur;

    // Highest index we can remove is size-1
    if (ll == NULL || index < 0 || index >= ll->size)
        return -1;

    // If removing first node, need to update head pointer
    if (index == 0)
    {
        cur = ll->head->next;
        free(ll->head);
        ll->head = cur;
        ll->size--;

        return 0;
    }

    // Find the nodes before and after the target position
    // Free the target node and reconnect the links
    if ((pre = findNode(ll, index - 1)) != NULL)
    {

        if (pre->next == NULL)
            return -1;

        cur = pre->next;
        pre->next = cur->next;
        free(cur);
        ll->size--;
        return 0;
    }

    return -1;
}
