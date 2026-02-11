add_elem(linked_list_t *l,void *elem)
{

  linked_element *ret=calloc(1,sizeof(linked_element));
  ret->stamp=l->current++;
  ret->ptr=elem;
  ret->list=l;

  if(l->head)
    l->head->prev=ret;
  else
    l->tail=ret;
  ret->next=l->head;
  ret->prev=NULL;
  l->head=ret;
  l->active++;

  return(ret);
}
