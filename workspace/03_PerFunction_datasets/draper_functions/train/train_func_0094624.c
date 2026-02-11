ib_fmr_cache_lookup(struct ib_fmr_pool *pool,
						      u64 *page_list,
						      int  page_list_len,
						      u64  io_virtual_address)
{
	struct hlist_head *bucket;
	struct ib_pool_fmr *fmr;

	if (!pool->cache_bucket)
		return NULL;

	bucket = pool->cache_bucket + ib_fmr_hash(*page_list);

	hlist_for_each_entry(fmr, bucket, cache_node)
		if (io_virtual_address == fmr->io_virtual_address &&
		    page_list_len      == fmr->page_list_len      &&
		    !memcmp(page_list, fmr->page_list,
			    page_list_len * sizeof *page_list))
			return fmr;

	return NULL;
}
