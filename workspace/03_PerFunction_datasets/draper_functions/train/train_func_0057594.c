slist_remove(slist_t *slist, void *key)
{
	GSList *item, *prev;

	slist_check(slist);
	g_assert(1 == slist->refcount);
	g_assert(slist->length > 0);

	prev = NULL;
	for (item = slist->head; NULL != item; item = g_slist_next(item)) {
		if (key == item->data) {
			slist_remove_item(slist, prev, item);
			return TRUE;
		}
		prev = item;
	}

	return FALSE;
}
