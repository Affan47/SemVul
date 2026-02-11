e_name_western_get_words_at_idx (gchar *str,
                                 gint idx,
                                 gint num_words)
{
	GString *words;
	gchar *p;
	gint   word_count;


	words = g_string_new ("");
	word_count = 0;
	p = str + idx;
	while (word_count < num_words && *p != '\0') {
		while (!g_unichar_isspace (g_utf8_get_char (p)) && *p != '\0') {
			words = g_string_append_unichar (words, g_utf8_get_char (p));
			p = g_utf8_next_char (p);
		}

		while (g_unichar_isspace (g_utf8_get_char (p)) && *p != '\0')
			p = g_utf8_next_char (p);

		word_count++;
	}

	return g_string_free (words, FALSE);
}
