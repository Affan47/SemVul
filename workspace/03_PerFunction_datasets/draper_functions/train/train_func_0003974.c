process_bio(struct cache *cache, struct prealloc *structs,
			struct bio *bio)
{
	int r;
	dm_oblock_t block = get_bio_block(cache, bio);
	struct dm_bio_prison_cell *cell_prealloc, *new_ocell;


	cell_prealloc = prealloc_get_cell(structs);
	r = bio_detain(cache, block, bio, cell_prealloc,
		       (cell_free_fn) prealloc_put_cell,
		       structs, &new_ocell);
	if (r > 0)
		return;

	process_cell(cache, structs, new_ocell);
}
