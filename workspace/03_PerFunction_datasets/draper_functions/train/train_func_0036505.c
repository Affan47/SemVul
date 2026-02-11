config_write_word(CONFIG_REC *rec, const char *word, int string)
{
	char *str;
	int ret;

	g_return_val_if_fail(rec != NULL, -1);
	g_return_val_if_fail(word != NULL, -1);

	if (!string && !config_has_specials(word))
		return config_write_str(rec, word);

	str = config_escape_string(word);
	ret = config_write_str(rec, str);
	g_free(str);

	return ret;
}
