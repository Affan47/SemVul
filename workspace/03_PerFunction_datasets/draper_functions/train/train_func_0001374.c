new_rdataset(dns_rbtdb_t *rbtdb, isc_mem_t *mctx)
{
	rdatasetheader_t *h;

	h = isc_mem_get(mctx, sizeof(*h));
	if (h == NULL)
		return (NULL);

#if TRACE_HEADER
	if (IS_CACHE(rbtdb) && rbtdb->common.rdclass == dns_rdataclass_in)
		fprintf(stderr, "allocated header: %p\n", h);
#endif
	init_rdataset(rbtdb, h);
	return (h);
}
