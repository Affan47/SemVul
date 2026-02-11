list_insert_before(list, data, bytes)
LIST *list;
char *data;
int bytes;
{
   LIST_ELEMENT *new;


   new = list_create_element(data, bytes);
   if (new == NULL)
      return(NULL);


   if (list->front == NULL) {

      new->prev = new->next = NULL;
      list->front = list->rear = list->curr = new;
   }
   else if (list->curr->prev == NULL) {

      new->prev = NULL;
      new->next = list->curr;
      list->curr->prev = new;
      list->front = new;
   }
   else {

      new->prev = list->curr->prev;
      list->curr->prev->next = new;
      new->next = list->curr;
      list->curr->prev = new;
   }

   list->curr = new;
   list->size++;
   return(new->data);
}
