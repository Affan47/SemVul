consume_line (FILE * in, GString * str)
{
	int ch;
	gsize bytes_read, bytes_written;
	gchar * utf;
	gboolean ret = TRUE;

	g_string_truncate (str, 0);

	while (ret && (ch = fgetc (in)) != EOF) {
		if (ch == '\r')
			continue;
		else {
			g_string_append_c (str, ch);
			if (ch == '\n')
				ret = FALSE;
		}
	}

	if (str->len) {
		utf = g_locale_to_utf8 (str->str, str->len, &bytes_read, &bytes_written, NULL);

		if (utf) {
			g_string_assign (str, utf);
			g_free (utf);
		}


	}

	return ret;
}
