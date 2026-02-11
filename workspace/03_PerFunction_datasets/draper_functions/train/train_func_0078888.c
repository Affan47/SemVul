get_line_and_column_from_filename(gchar *filename, gint *line, gint *column)
{
	gsize i;
	gint colon_count = 0;
	gboolean have_number = FALSE;
	gsize len;

	g_assert(*line == -1 && *column == -1);

	if (G_UNLIKELY(! NZV(filename)))
		return;


	if (g_file_test(filename, G_FILE_TEST_EXISTS))
		return;

	len = strlen(filename);
	for (i = len - 1; i >= 1; i--)
	{
		gboolean is_colon = filename[i] == ':';
		gboolean is_digit = g_ascii_isdigit(filename[i]);

		if (! is_colon && ! is_digit)
			break;

		if (is_colon)
		{
			if (++colon_count > 1)
				break;
		}
		else
			colon_count = 0;

		if (is_digit)
			have_number = TRUE;

		if (is_colon && have_number)
		{
			gint number = atoi(&filename[i + 1]);

			filename[i] = '\0';
			have_number = FALSE;

			*column = *line;
			*line = number;
		}

		if (*column >= 0)
			break;
	}
}
