slist_remove_item(slist_t *slist, GSList *prev, GSList *item)
{
	g_assert(item);

	g_assert(!prev || g_slist_next(prev) == item);

	if (item == slist->head) {
		g_assert(NULL == prev);
		slist->head = g_slist_next(slist->head);
	}
	if (item == slist->tail) {
		slist->tail = prev;
	}


	item = g_slist_delete_link(prev ? prev : item, item);

	slist->length--;
	slist->stamp++;

	slist_regression(slist);
}
