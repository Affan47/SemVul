regcache_sync_block(struct regmap *map, void *block,
			unsigned long *cache_present,
			unsigned int block_base, unsigned int start,
			unsigned int end)
{
	if (regmap_can_raw_write(map) && !map->use_single_write)
		return regcache_sync_block_raw(map, block, cache_present,
					       block_base, start, end);
	else
		return regcache_sync_block_single(map, block, cache_present,
						  block_base, start, end);
}
