add_pattern_suffix(void *cbdata, const char *suffix, size_t suffix_len, const struct regex_list *iregex)
{
	struct regex_matcher *matcher = cbdata;
	struct regex_list *regex = cli_malloc(sizeof(*regex));
	const struct cli_element *el;

	assert(matcher);
	if(!regex) {
        cli_errmsg("add_pattern_suffix: Unable to allocate memory for regex\n");
		return CL_EMEM;
    }
	regex->pattern = iregex->pattern ? cli_strdup(iregex->pattern) : NULL;
	regex->preg = iregex->preg;
	regex->nxt = NULL;
	el = cli_hashtab_find(&matcher->suffix_hash, suffix, suffix_len);


	if(el) {

		assert((size_t)el->data < matcher->suffix_cnt);
		list_add_tail(&matcher->suffix_regexes[el->data], regex);
	} else {

		size_t n = matcher->suffix_cnt++;
		el = cli_hashtab_insert(&matcher->suffix_hash, suffix, suffix_len, n);
		matcher->suffix_regexes = cli_realloc(matcher->suffix_regexes, (n+1)*sizeof(*matcher->suffix_regexes));
		if(!matcher->suffix_regexes) {
			free (regex);
			return CL_EMEM;
		}
		matcher->suffix_regexes[n].tail = regex;
		matcher->suffix_regexes[n].head = regex;
		if (suffix[0] == '/' && suffix[1] == '\0')
		    matcher->root_regex_idx = n;
		add_newsuffix(matcher, regex, suffix, suffix_len);
	}
	return 0;
}
