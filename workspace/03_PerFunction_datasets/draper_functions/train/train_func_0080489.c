prepend_element(struct llist *list, void *data)
{
	struct list_elem *el_p;

	el_p = malloc(sizeof(struct list_elem));
	if (NULL == el_p) return FAILURE;
	el_p->data = data;
	el_p->next = NULL;

	if (NULL == list->head)  {
		list->head = el_p;
		list->tail = el_p;
	} else {
		el_p->next = list->head;
		list->head = el_p;
	}
	list->count += 1;

	return SUCCESS;
}
