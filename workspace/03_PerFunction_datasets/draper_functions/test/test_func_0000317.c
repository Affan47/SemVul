anjuta_session_get_strv (AnjutaSession *session, const gchar *section, const gchar *key)
{
	GList *list;
	gchar **value = NULL;

	list = anjuta_session_get_string_list (session, section, key);

	if (list != NULL)
	{
		gchar **var;
		GList *node;

		value = g_new (gchar *, g_list_length (list) + 1);
		var = value;
		for (node = g_list_first (list); node != NULL; node = g_list_next (node))
		{
			*var = (gchar *)node->data;
			++var;
		}
		*var = NULL;
	}

	return value;
}
