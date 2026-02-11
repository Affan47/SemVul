dns_diff_append(dns_diff_t *diff, dns_difftuple_t **tuplep)
{
	ISC_LIST_APPEND(diff->tuples, *tuplep, link);
	*tuplep = NULL;
}
