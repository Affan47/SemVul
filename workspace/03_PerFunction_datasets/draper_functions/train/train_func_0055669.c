dm_bio_prison_create(void)
{
	struct dm_bio_prison *prison = kmalloc(sizeof(*prison), GFP_KERNEL);

	if (!prison)
		return NULL;

	spin_lock_init(&prison->lock);

	prison->cell_pool = mempool_create_slab_pool(MIN_CELLS, _cell_cache);
	if (!prison->cell_pool) {
		kfree(prison);
		return NULL;
	}

	prison->cells = RB_ROOT;

	return prison;
}
