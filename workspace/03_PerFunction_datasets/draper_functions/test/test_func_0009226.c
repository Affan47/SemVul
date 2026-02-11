gkrellm_string_in_list(GList *list, gchar *s)
	{
	if (!s)
		return NULL;
	for ( ; list; list = list->next)
		{
		if (!strcmp((gchar *) list->data, s))
			return list;
		}
	return NULL;
	}
