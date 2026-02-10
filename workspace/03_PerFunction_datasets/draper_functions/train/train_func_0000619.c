_g_settings_set_string_list (GSettings  *settings,
			     const char *key,
			     GList      *list)
{
	int     len;
	char  **strv;
	int     i;
	GList  *scan;

	len = g_list_length (list);
	strv = g_new (char *, len + 1);
	for (i = 0, scan = list; scan; scan = scan->next)
		strv[i++] = scan->data;
	strv[i] = NULL;

	g_settings_set_strv (settings, key, (const char *const *) strv);

	g_free (strv);
}
