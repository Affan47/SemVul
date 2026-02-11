keywords_to_string(FileData *fd)
{
	GList *keywords;
	GString *kwstr = NULL;
	gchar *ret = NULL;

	g_assert(fd);

	keywords = metadata_read_list(fd, KEYWORD_KEY, METADATA_PLAIN);

	if (keywords)
		{
		GList *work = keywords;

		while (work)
			{
			gchar *kw = work->data;
			work = work->next;

			if (!kw) continue;
			if (!kwstr)
				kwstr = g_string_new("");
			else
				g_string_append(kwstr, ", ");

			g_string_append(kwstr, kw);
			}
		string_list_free(keywords);
		}

	if (kwstr)
		{
		ret = kwstr->str;
		g_string_free(kwstr, FALSE);
		}

	return ret;
}
