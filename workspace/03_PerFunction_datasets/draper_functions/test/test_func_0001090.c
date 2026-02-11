e_name_western_extract_middle (ENameWestern *name,
                               ENameWesternIdxs *idxs)
{
	gchar *word;
	gchar *middle;


	if (idxs->first_idx == -1)
		return;

	middle = name->full + idxs->first_idx + strlen (name->first);
	if (*middle == '\0')
		return;

	middle = g_utf8_next_char (middle);
	if (*middle == '\0')
		return;


	while (g_unichar_isspace (g_utf8_get_char (middle)) &&
	       *middle != '\0')
		middle = g_utf8_next_char (middle);

	if (*middle == '\0')
		return;


	if (*middle == '\"') {
		if (idxs->nick_idx == -1)
			return;

		middle = name->full + idxs->nick_idx + strlen (name->nick);
		middle = g_utf8_next_char (middle);

		while (g_unichar_isspace (g_utf8_get_char (middle)) &&
		       *middle != '\0')
			middle = g_utf8_next_char (middle);

		if (*middle == '\0')
			return;
	}


	word = e_name_western_get_words_at_idx (name->full, middle - name->full, 1);
	if (e_name_western_is_complex_last_beginning (word)) {
		g_free (word);
		return;
	}


	e_name_western_cleanup_string (& word);
	if (e_name_western_word_is_suffix (word)) {
		g_free (word);
		return;
	}


	if (word[0] == '\"') {
		g_free (word);
		return;
	}

	idxs->middle_idx = middle - name->full;
	name->middle = word;
}
