list_insert_after(LIST *list, POINTER data)
{
	LIST *l1 = NULL, *l2 = NULL;
	LIST *l;

	if(!list) return list_append(NULL, data);


	l1 = list;
	l2 = list->next;

	l = os_new(LIST, 1);
	l->prev=l1;
	l->next = l2;
	l->data = data;


	if(l1) l1->next = l;
	if(l2) l2->prev = l;


	while(list->prev) list=list->prev;

	return list;
}
