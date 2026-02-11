list_shift(list_t *list)
{
	GList *item;
	void *key;
	bool found;

	list_check(list);

	item = list->head;
	if (NULL == item)
		return NULL;

	key = item->data;
	found = list_remove(list, key);

	g_assert(found);

	return key;
}
