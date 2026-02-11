menu_escape_underscores_and_prepend (const char *text)
{
	GString    *escaped_text;
	const char *src;
	int         inserted;

	if (!text)
		return g_strdup (text);

	escaped_text = g_string_sized_new (strlen (text) + 1);
	g_string_printf (escaped_text, "_%s", text);

	src = text;
	inserted = 1;

	while (*src) {
		gunichar c;

		c = g_utf8_get_char (src);

		if (c == (gunichar)-1) {
			g_warning ("Invalid input string for underscore escaping");
			return g_strdup (text);
		} else if (c == '_') {
			g_string_insert_c (escaped_text,
					   src - text + inserted, '_');
			inserted++;
		}

		src = g_utf8_next_char (src);
	}

	return g_string_free (escaped_text, FALSE);
}
