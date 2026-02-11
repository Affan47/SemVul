thin_iterate_devices(struct dm_target *ti,
				iterate_devices_callout_fn fn, void *data)
{
	sector_t blocks;
	struct thin_c *tc = ti->private;
	struct pool *pool = tc->pool;


	if (!pool->ti)
		return 0;

	blocks = pool->ti->len;
	(void) sector_div(blocks, pool->sectors_per_block);
	if (blocks)
		return fn(ti, tc->pool_dev, 0, pool->sectors_per_block * blocks, data);

	return 0;
}
