suffix_match(struct outline_file *file, const char *word, struct result *res)
{
    struct entry x, *ep;
    int rc;

    if (init_suffix_index(file)) {
	dico_log(L_ERR, 0, "not enough memory");
	return 1;
    }

    x.length = strlen(word);
    x.word = malloc(x.length + 1);
    if (!x.word) {
	dico_log(L_ERR, 0, "not enough memory");
	return 1;
    }
    x.wordlen = utf8_strlen(word);

    revert_word(x.word, word, x.length);

    ep = bsearch(&x, file->suf_index, file->count, sizeof(file->suf_index[0]),
		 compare_prefix);
    if (ep) {
	struct entry *p, **epp;
	size_t count = 1;

	for (p = ep - 1; p > file->suf_index && compare_prefix(&x, p) == 0;
	     p--)
	    count++;
	for (ep++; ep < file->suf_index + file->count
		 && compare_prefix(&x, ep) == 0; ep++)
	    count++;
	p++;

	epp = calloc(count, sizeof(*epp));
	if (!epp) {
	    dico_log(L_ERR, 0, "not enough memory");
	    rc = 1;
	} else {
	    res->type = result_match_list;
	    res->v.list = dico_list_create();
	    if (!res->v.list) {
		dico_log(L_ERR, 0, "not enough memory");
		rc = 1;
	    } else {
		size_t i;

		for (i = 0; i < count; i++)
		    epp[i] = p[i].peer;
		qsort(epp, count, sizeof(epp[0]), compare_entry_ptr);

		for (i = 0; i < count; i++)
		    dico_list_append(res->v.list, epp[i]);
		res->count = dico_list_count(res->v.list);
		rc = 0;
	    }
	    free(epp);
	}
    } else
	rc = 1;
    free(x.word);
    return rc;
}
