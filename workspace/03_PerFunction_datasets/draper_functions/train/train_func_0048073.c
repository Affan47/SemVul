create_word_tokenizer(const char *string)
{
	struct word_tokenizer *wt = malloc(sizeof(struct word_tokenizer));
	if (NULL == wt) return NULL;

	wt->string = strdup(string);
	wt->string_len = strlen(wt->string);
	wt->word_start = wt->string;
	wt->word_stop = NULL;

	return wt;
}
