process_prepared_discard_passdown(struct dm_thin_new_mapping *m)
{
	int r;
	struct thin_c *tc = m->tc;
	struct pool *pool = tc->pool;

	r = dm_thin_remove_range(tc->td, m->virt_begin, m->virt_end);
	if (r)
		metadata_operation_failed(pool, "dm_thin_remove_range", r);

	else if (m->maybe_shared)
		r = passdown_double_checking_shared_status(m);
	else
		r = issue_discard(tc, m->data_block, m->data_block + (m->virt_end - m->virt_begin), m->bio);


	m->bio->bi_error = r;
	bio_endio(m->bio);
	cell_defer_no_holder(tc, m->cell);
	mempool_free(m, pool->mapping_pool);
}
