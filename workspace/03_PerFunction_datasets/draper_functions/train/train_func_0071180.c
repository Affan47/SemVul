pref_list_set(const gchar *group, const gchar *key, const gchar *marker, const gchar *text)
{
	gchar *token;
	gchar *path;
	GList *work;

	if (!group || !key || !marker) return;

	token = g_strconcat(key, marker, NULL);
	path = g_strconcat(token, text, NULL);

	work = pref_list_find(group, token);
	if (work)
		{
		gchar *old_path = work->data;

		if (text)
			{
			work->data = path;
			path = NULL;

			g_free(old_path);
			}
		else
			{
			history_list_item_remove(group, old_path);
			}
		}
	else if (text)
		{
		history_list_add_to_key(group, path, 0);
		}

	g_free(path);
	g_free(token);
}
