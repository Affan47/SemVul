sl_list_add(SL_LIST *list, void *el)
{
	SL_LIST_ITEM *it = malloc(sizeof(SL_LIST_ITEM));
	if (NULL == it) {printf("Out of space\n");exit(-1);}
	it->next = list->root;
	if (NULL != list->root) {list->root->prev = it;}
	it->item = el;
	it->prev = NULL;
	list->root = it;
	return 0;
}
