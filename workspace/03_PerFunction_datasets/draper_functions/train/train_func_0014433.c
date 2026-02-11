pcre_sel(int cmd, dico_key_t key, const char *dict_word)
{
    int rc = 0;
    char const *word = key->word;
    pcre *pre = key->call_data;

    switch (cmd) {
    case DICO_SELECT_BEGIN:
	pre = compile_pattern(word);
	if (!pre)
	    return 1;
	key->call_data = pre;
	break;

    case DICO_SELECT_RUN:
	rc = pcre_exec(pre, 0, dict_word, strlen(dict_word), 0, 0,
		       NULL, 0) >= 0;
	break;

    case DICO_SELECT_END:
	pcre_free(pre);
	break;
    }
    return rc;
}
