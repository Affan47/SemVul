format_add_lineend(const char *text, const char *linestart)
{
	GString *str;
	char *ret;

	if (linestart == NULL)
		return g_strdup(text);

	if (strchr(text, '\n') == NULL)
		return g_strconcat(text, linestart, NULL);

	str = g_string_new(NULL);
	while (*text != '\0') {
		if (*text == '\n')
			g_string_append(str, linestart);
		g_string_append_c(str, *text);
		text++;
	}
	g_string_append(str, linestart);

	ret = str->str;
	g_string_free(str, FALSE);
	return ret;
}
