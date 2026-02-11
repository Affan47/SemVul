debug_send_evaluate(char token, gint scid, const gchar *expr)
{
	char *locale = utils_get_locale_from_utf8(expr);
	GString *string = g_string_sized_new(strlen(locale));
	const char *s;

	for (s = locale; *s; s++)
	{
		if (*s == '"' || *s == '\\')
			g_string_append_c(string, '\\');
		g_string_append_c(string, *s);
	}

	debug_send_format(F, "0%c%d-data-evaluate-expression \"%s\"", token, scid, string->str);
	g_string_free(string, TRUE);

	return locale;
}
