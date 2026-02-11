list_free_strings(GList *list)
{
	list = g_list_first(list);

	while (list != NULL) {
		g_free(list->data);
		list = list->next;
	}
}
