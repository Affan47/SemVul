complete_trans_path_choice(const char *line, const char *word, int pos, int state)
{
	int which = 0;
	int wordlen = strlen(word);
	int i;
	char *ret = NULL;
	size_t len = 0;
	const struct ast_format_list *format_list = ast_format_list_get(&len);

	for (i = 0; i < len; i++) {
		if (AST_FORMAT_GET_TYPE(format_list[i].format.id) != AST_FORMAT_TYPE_AUDIO) {
			continue;
		}
		if (!strncasecmp(word, format_list[i].name, wordlen) && ++which > state) {
			ret = ast_strdup(format_list[i].name);
			break;
		}
	}
	ast_format_list_destroy(format_list);
	return ret;
}
