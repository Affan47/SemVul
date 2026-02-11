add_search(irs_resconf_t *conf, char *domain) {
	irs_resconf_search_t *entry;

	entry = isc_mem_get(conf->mctx, sizeof(*entry));
	if (entry == NULL)
		return (ISC_R_NOMEMORY);

	entry->domain = domain;
	ISC_LINK_INIT(entry, link);
	ISC_LIST_APPEND(conf->searchlist, entry, link);

	return (ISC_R_SUCCESS);
}
