match_last_chars(ScintillaObject *sci, gint pos, const gchar *str)
{
	gsize len = strlen(str);
	gchar *buf;

	g_return_val_if_fail(len < 100, FALSE);

	buf = g_alloca(len + 1);
	sci_get_text_range(sci, pos - len, pos, buf);
	return strcmp(str, buf) == 0;
}
