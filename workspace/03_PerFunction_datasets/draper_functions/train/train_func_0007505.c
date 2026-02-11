lwres_conf_parsedomain(lwres_context_t *ctx,  FILE *fp) {
	char word[LWRES_CONFMAXLINELEN];
	int res, i;
	lwres_conf_t *confdata;

	confdata = &ctx->confdata;

	res = getword(fp, word, sizeof(word));
	if (strlen(word) == 0U)
		return (LWRES_R_FAILURE);
	else if (res == ' ' || res == '\t')
		res = eatwhite(fp);

	if (res != EOF && res != '\n')
		return (LWRES_R_FAILURE);

	if (confdata->domainname != NULL)
		CTXFREE(confdata->domainname,
			strlen(confdata->domainname) + 1);


	for (i = 0; i < LWRES_CONFMAXSEARCH; i++) {
		if (confdata->search[i] != NULL) {
			CTXFREE(confdata->search[i],
				strlen(confdata->search[i])+1);
			confdata->search[i] = NULL;
		}
	}
	confdata->searchnxt = 0;

	confdata->domainname = lwres_strdup(ctx, word);

	if (confdata->domainname == NULL)
		return (LWRES_R_FAILURE);

	return (LWRES_R_SUCCESS);
}
