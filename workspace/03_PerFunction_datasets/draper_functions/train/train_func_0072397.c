bio_detain_range(struct cache *cache, dm_oblock_t oblock_begin, dm_oblock_t oblock_end,
			    struct bio *bio, struct dm_bio_prison_cell *cell_prealloc,
			    cell_free_fn free_fn, void *free_context,
			    struct dm_bio_prison_cell **cell_result)
{
	int r;
	struct dm_cell_key key;

	build_key(oblock_begin, oblock_end, &key);
	r = dm_bio_detain(cache->prison, &key, bio, cell_prealloc, cell_result);
	if (r)
		free_fn(free_context, cell_prealloc);

	return r;
}
