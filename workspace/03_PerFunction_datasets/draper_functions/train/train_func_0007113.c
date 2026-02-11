parse_file_line(ParseData *data, gchar **filename, gint *line)
{
	gchar *end = NULL;
	gchar **fields;

	*filename = NULL;
	*line = -1;

	g_return_if_fail(data->string != NULL);

	fields = g_strsplit_set(data->string, data->pattern, data->min_fields);


	if (g_strv_length(fields) < data->min_fields)
	{
		g_strfreev(fields);
		return;
	}

	*line = strtol(fields[data->line_idx], &end, 10);


	if (fields[data->line_idx] == end)
	{
		g_strfreev(fields);
		return;
	}


	if (data->file_idx == -1)
	{

		GeanyDocument *doc = document_get_current();
		if (doc != NULL)
			*filename = g_strdup(doc->file_name);
		g_strfreev(fields);
		return;
	}

	*filename = g_strdup(fields[data->file_idx]);
	g_strfreev(fields);
}
