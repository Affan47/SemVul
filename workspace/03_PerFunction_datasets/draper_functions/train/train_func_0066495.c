window_item_find(void *server, const char *name)
{
	WI_ITEM_REC *item;
	GSList *tmp;

	g_return_val_if_fail(name != NULL, NULL);

	for (tmp = windows; tmp != NULL; tmp = tmp->next) {
		WINDOW_REC *rec = tmp->data;

		item = window_item_find_window(rec, server, name);
		if (item != NULL) return item;
	}

	return NULL;
}
