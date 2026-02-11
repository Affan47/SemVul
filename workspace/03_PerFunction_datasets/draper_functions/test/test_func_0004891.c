complete_ulimit(struct ast_cli_args *a)
{
	int which = 0, i;
	int wordlen = strlen(a->word);

	if (a->pos > 1)
		return NULL;
	for (i = 0; i < ARRAY_LEN(limits); i++) {
		if (!strncasecmp(limits[i].clicmd, a->word, wordlen)) {
			if (++which > a->n)
				return ast_strdup(limits[i].clicmd);
		}
	}
	return NULL;
}
