e_name_western_get_preceding_word (gchar *str,
                                   gint idx)
{
	gint   word_len;
	gchar *word;
	gchar *p;

	p = str + idx;

	while (g_unichar_isspace (g_utf8_get_char (p)) && p > str)
		p = g_utf8_prev_char (p);

	while (!g_unichar_isspace (g_utf8_get_char (p)) && p > str)
		p = g_utf8_prev_char (p);

	if (g_unichar_isspace (g_utf8_get_char (p)))
		p = g_utf8_next_char (p);

	word_len = (str + idx) - p;
	word = g_malloc0 (word_len + 1);
	if (word_len > 0)
		strncpy (word, p, word_len);

	return word;
}
