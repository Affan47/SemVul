issue_copy(struct dm_cache_migration *mg)
{
	int r;
	struct dm_io_region o_region, c_region;
	struct cache *cache = mg->cache;
	sector_t cblock = from_cblock(mg->cblock);

	o_region.bdev = cache->origin_dev->bdev;
	o_region.count = cache->sectors_per_block;

	c_region.bdev = cache->cache_dev->bdev;
	c_region.sector = cblock * cache->sectors_per_block;
	c_region.count = cache->sectors_per_block;

	if (mg->writeback || mg->demote) {

		o_region.sector = from_oblock(mg->old_oblock) * cache->sectors_per_block;
		r = dm_kcopyd_copy(cache->copier, &c_region, 1, &o_region, 0, copy_complete, mg);
	} else {

		o_region.sector = from_oblock(mg->new_oblock) * cache->sectors_per_block;
		r = dm_kcopyd_copy(cache->copier, &o_region, 1, &c_region, 0, copy_complete, mg);
	}

	if (r < 0) {
		DMERR_LIMIT("%s: issuing migration failed", cache_device_name(cache));
		migration_failure(mg);
	}
}
