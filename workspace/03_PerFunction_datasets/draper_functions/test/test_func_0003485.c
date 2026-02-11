escape_string (const char *string)
{
	const char *start, *inptr;
	GString *str;
	char *buf;

	str = g_string_new ("");

	inptr = string;

	while (*inptr) {
		start = inptr;
		while (*inptr && *inptr != '"')
			inptr++;

		g_string_append_len (str, start, inptr - start);
		if (*inptr == '"') {
			g_string_append (str, "\\\"");
			inptr++;
		}
	}

	buf = str->str;
	g_string_free (str, FALSE);

	return buf;
}
