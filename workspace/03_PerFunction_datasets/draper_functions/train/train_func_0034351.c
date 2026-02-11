pl3_file_browser_is_search(const int num_field, const gchar * search_string, GError ** error)
{
	MpdData *data_t = NULL;
	if (num_field == MPD_TAG_NUM_OF_ITEM_TYPES)
	{
		data_t = advanced_search(search_string, FALSE);
	} else
	{
		gchar **splitted = tokenize_string(search_string);
		int i = 0;
		gboolean found = FALSE;
		for (i = 0; splitted && splitted[i]; i++)
		{
			if (!found)
			{
				mpd_database_search_start(connection, FALSE);
				found = TRUE;
			}
			mpd_database_search_add_constraint(connection, num_field, splitted[i]);
		}
		if (splitted)
			g_strfreev(splitted);
		if (found)
		{
			data_t = mpd_database_search_commit(connection);
		}
	}
	return data_t;
}
