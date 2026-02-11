zend_llist_copy(zend_llist *dst, zend_llist *src)
{
	zend_llist_element *ptr;

	zend_llist_init(dst, src->size, src->dtor, src->persistent);
	ptr = src->head;
	while (ptr) {
		zend_llist_add_element(dst, ptr->data);
		ptr = ptr->next;
	}
}
