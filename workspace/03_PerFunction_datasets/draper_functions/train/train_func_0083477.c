slist_to_strv (GSList *list)
{
	gchar **res;
	guint i = 0;

	res = g_new (gchar *, g_slist_length (list) + 1);

	for ( ; list != NULL; list = list->next)
	{
		res[i] = list->data;
		++i;
	}

	res[i] = NULL;

	return res;
}
