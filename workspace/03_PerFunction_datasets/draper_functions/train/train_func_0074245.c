dm_region_hash_destroy(struct dm_region_hash *rh)
{
	unsigned h;
	struct dm_region *reg, *nreg;

	BUG_ON(!list_empty(&rh->quiesced_regions));
	for (h = 0; h < rh->nr_buckets; h++) {
		list_for_each_entry_safe(reg, nreg, rh->buckets + h,
					 hash_list) {
			BUG_ON(atomic_read(&reg->pending));
			mempool_free(reg, rh->region_pool);
		}
	}

	if (rh->log)
		dm_dirty_log_destroy(rh->log);

	mempool_destroy(rh->region_pool);
	vfree(rh->buckets);
	kfree(rh);
}
