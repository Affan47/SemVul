zend_llist_add_element(zend_llist *l, void *element)
{
	zend_llist_element *tmp = pemalloc(sizeof(zend_llist_element)+l->size-1, l->persistent);

	tmp->prev = l->tail;
	tmp->next = NULL;
	if (l->tail) {
		l->tail->next = tmp;
	} else {
		l->head = tmp;
	}
	l->tail = tmp;
	memcpy(tmp->data, element, l->size);

	++l->count;
}
