clean_stale_headers(dns_rbtdb_t *rbtdb, isc_mem_t *mctx, rdatasetheader_t *top)
{
	rdatasetheader_t *d, *down_next;

	for (d = top->down; d != NULL; d = down_next) {
		down_next = d->down;
		free_rdataset(rbtdb, mctx, d);
	}
	top->down = NULL;
}
