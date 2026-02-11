live_search_match_prefix (const gchar *string, const gchar *prefix)
{
	const gchar *p;
	const gchar *prefix_p;
	gboolean next_word = FALSE;

	if (prefix == NULL || prefix[0] == 0)
		return TRUE;

	if (string == NULL || *string == '\0')
		return FALSE;

	prefix_p = prefix;
	for (p = string; *p != '\0'; p = g_utf8_next_char (p)) {
		gunichar sc;


		sc = stripped_char (g_utf8_get_char (p));
		if (sc == 0)
			continue;


		if (next_word && g_unichar_isalnum (sc))
			continue;
		next_word = FALSE;


		if (!g_unichar_isalnum (sc))
			continue;


		if (sc != g_utf8_get_char (prefix_p)) {
			next_word = TRUE;
			prefix_p = prefix;
			continue;
		}


		prefix_p = g_utf8_next_char (prefix_p);
		if (*prefix_p == '\0')
			return TRUE;
	}

	return FALSE;
}
