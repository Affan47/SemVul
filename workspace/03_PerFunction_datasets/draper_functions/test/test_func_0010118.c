nprefix_sel(int cmd, dico_key_t key, const char *dict_word)
{
    char const *key_word = key->word;
    struct nprefix *np;
    size_t wordlen;

    switch (cmd) {
    case DICO_SELECT_BEGIN: {
	char *p;
	size_t skip, count;

	np = calloc(1, sizeof(np[0]));
	if (!np) {
	    dico_log(L_ERR, errno, "nprefix_sel");
	    return 1;
	}
	np->prefix = (char*)key_word;
	np->lim = 0;
	skip = strtoul(key_word, &p, 10);
	if (*p == '#') {
	    count = strtoul(p + 1, &p, 10);
	    if (*p == '#') {
		np->prefix = p + 1;
		np->skip = skip;
		np->count = count;
		np->lim = 1;
	    }
	}
	np->pfxlen = utf8_strlen(np->prefix);
	key->call_data = np;
	break;
    }

    case DICO_SELECT_RUN:
	np = key->call_data;
	if (np->last_match_str &&
	    utf8_strcasecmp((char*)dict_word, np->last_match_str) == 0)
	    return 0;
	if (np->lim && np->n > np->skip + np->count)
	    return 0;
	wordlen = utf8_strlen(dict_word);
	if (wordlen >= np->pfxlen &&
	    utf8_strncasecmp((char*)dict_word, np->prefix, np->pfxlen) == 0) {
	    size_t s = strlen(dict_word) + 1;
	    if (np->last_match_len < s) {
		char *p = realloc(np->last_match_str, s);
		if (!p)
		    return 0;

		np->last_match_str = p;
		np->last_match_len = s;
	    }
	    strcpy(np->last_match_str, dict_word);
	    if (!np->lim)
		return 1;
	    np->n++;
	    return np->n > np->skip && np->n <= np->skip + np->count;
	}
	break;

    case DICO_SELECT_END:
	np = key->call_data;
	free(np->last_match_str);
	free(np);
	break;
    }
    return 0;
}
