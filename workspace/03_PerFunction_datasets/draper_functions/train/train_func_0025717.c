resconf_parsesearch(irs_resconf_t *conf,  FILE *fp) {
	int idx, delim;
	char word[RESCONFMAXLINELEN];

	if (conf->domainname != NULL) {


		isc_mem_free(conf->mctx, conf->domainname);
		conf->domainname = NULL;
	}


	for (idx = 0; idx < RESCONFMAXSEARCH; idx++) {
		if (conf->search[idx] != NULL) {
			isc_mem_free(conf->mctx, conf->search[idx]);
			conf->search[idx] = NULL;
		}
	}
	conf->searchnxt = 0;

	delim = getword(fp, word, sizeof(word));
	if (strlen(word) == 0U)
		return (ISC_R_UNEXPECTEDEND);

	idx = 0;
	while (strlen(word) > 0U) {
		if (conf->searchnxt == RESCONFMAXSEARCH)
			goto ignore;

		conf->search[idx] = isc_mem_strdup(conf->mctx, word);
		if (conf->search[idx] == NULL)
			return (ISC_R_NOMEMORY);
		idx++;
		conf->searchnxt++;

	ignore:
		if (delim == EOF || delim == '\n')
			break;
		else
			delim = getword(fp, word, sizeof(word));
	}

	return (ISC_R_SUCCESS);
}
