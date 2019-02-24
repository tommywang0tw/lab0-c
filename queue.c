/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
        printf("can't allocate space for the queue.\n");
        return NULL;
    }
    q->size = 0;
    q->head = NULL;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL) {
        return;
    }
    list_ele_t *prev = q->head;
    list_ele_t *temp = q->head;
    while (temp != NULL) {
        free(temp->value);
        prev = temp;
        temp = temp->next;
        free(prev);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /*Handle q not-existing situation*/
    if (q == NULL) {
        printf("This queue doesn't exist!\n");
        return false;
    }
    list_ele_t *newh;
    int str_size;
    char *copy_s;
    /* What should you do if the q is NULL? */
    /* If q is NULL, we new a queue and then
    insert the element to the head of this queue*/
    str_size = strlen(s) + 1;
    copy_s = malloc(str_size * sizeof(char));
    if (copy_s == NULL) {
        printf("Couldn't allocate space for the string!\n");
        return false;
    }
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        printf("Couldn't allocate space for the element!\n");
        free(copy_s);
        return false;
    }
    strcpy(copy_s, s);
    /*Handle empty queue situation*/
    if (q->head == NULL) {
        q->head = newh;
        q->tail = newh;
        q->head->next = NULL;
        q->head->value = copy_s;
        q->size++;
        return true;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    newh->value = copy_s;
    q->head = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /*Handle queue not-existing situation*/
    if (q == NULL) {
        printf("This queue doesn't exist!\n");
        return false;
    }
    list_ele_t *newt;
    char *copy_s;
    int str_size;
    str_size = strlen(s) + 1;
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL) {
        printf("Couldn't allocate space for the element!\n");
        return false;
    }
    copy_s = malloc(str_size * sizeof(char));
    if (copy_s == NULL) {
        printf("Couldn't allocate space for the string!\n");
        free(newt);
        return false;
    }
    strcpy(copy_s, s);
    newt->value = copy_s;
    newt->next = NULL;
    /*Handle empty queue situation*/
    if (q->head == NULL) {
        q->head = newt;
        q->tail = newt;
        q->size++;
        return true;
    }
    q->tail->next = newt;
    q->tail = newt;
    q->size++;
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /*If queue is empty or NULL*/
    if (q == NULL || q->head == NULL)
        return false;
    /*If sp is non-NULL, copy the string about to be removed to it*/
    /*the maximum copied string size is bufsize-1*/
    if (sp != NULL) {
        strncpy(sp, q->head->value, bufsize - 1);
        *(sp + bufsize - 1) = '\0';
    }
    /*Free the space*/
    list_ele_t *temp = q->head;
    q->head = q->head->next;
    free(temp->value);
    free(temp);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return 0;
    }
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    /*Handle empty queue and non-existing queue*/
    if (q == NULL || q->head == NULL)
        return;

    list_ele_t *temp, *prev, *next;
    prev = q->head;
    temp = prev->next;
    next = temp;
    q->head->next = NULL;
    q->tail = q->head;
    while (temp != NULL) {
        next = temp->next;
        temp->next = prev;
        prev = temp;
        temp = next;
    }
    q->head = prev;
    return;
}
