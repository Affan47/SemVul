list_check(const list_t *list)
{
	g_assert(list);
	g_assert(LIST_MAGIC == list->magic);
	g_assert(list->refcount > 0);
	g_assert(list->length >= 0);
	g_assert(equiv(list->length == 0, !list->head && !list->tail));

	list_regression(list);
}
