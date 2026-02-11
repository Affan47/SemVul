list_insert_sorted(list_t *list, const void *key, GCompareFunc func)
{
	list_check(list);
	g_assert(1 == list->refcount);
	g_assert(func);

	list->head = g_list_insert_sorted(list->head,
		deconstify_pointer(key), func);
	if (list->tail) {
		list->tail = g_list_last(list->tail);
	} else {
		list->tail = list->head;
	}

	list->length++;
	list->stamp++;

	list_regression(list);
}
