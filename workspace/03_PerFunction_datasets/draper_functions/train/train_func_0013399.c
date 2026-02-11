auto_word_complete(const char *line, int *pos)
{
	GString *result;
	const char *replace;
	char *word, *wordstart, *ret;
	int startpos;

	g_return_val_if_fail(line != NULL, NULL);
	g_return_val_if_fail(pos != NULL, NULL);

	word = get_word_at(line, *pos, &wordstart);
	startpos = (int) (wordstart-line);

	result = g_string_new(line);
	g_string_erase(result, startpos, strlen(word));


	replace = completion_find(word, TRUE);
	if (replace == NULL) {
		ret = NULL;
		g_string_free(result, TRUE);
	} else {
		*pos = startpos+strlen(replace);

		g_string_insert(result, startpos, replace);
		ret = result->str;
		g_string_free(result, FALSE);
	}

	g_free(word);
	return ret;
}
