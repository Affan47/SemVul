diff_window_copy_list (GList *list)
{
	GList *copy = NULL;

	while (list) {
		copy = g_list_prepend (copy, g_strdup ((gchar *) list->data));
		list = list->next;
	}

	return g_list_reverse (copy);
}
