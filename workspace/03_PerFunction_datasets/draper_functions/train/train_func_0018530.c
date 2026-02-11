check_noentry(dns_acache_t *acache) {
	if (ISC_LIST_EMPTY(acache->entries) && acache->dbentries == 0) {
		return (ISC_TRUE);
	}

	return (ISC_FALSE);
}
