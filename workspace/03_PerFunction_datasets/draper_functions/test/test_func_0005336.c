reada_find_zone(struct btrfs_fs_info *fs_info,
					  struct btrfs_device *dev, u64 logical,
					  struct btrfs_bio *bbio)
{
	int ret;
	struct reada_zone *zone;
	struct btrfs_block_group_cache *cache = NULL;
	u64 start;
	u64 end;
	int i;

	zone = NULL;
	spin_lock(&fs_info->reada_lock);
	ret = radix_tree_gang_lookup(&dev->reada_zones, (void **)&zone,
				     logical >> PAGE_CACHE_SHIFT, 1);
	if (ret == 1)
		kref_get(&zone->refcnt);
	spin_unlock(&fs_info->reada_lock);

	if (ret == 1) {
		if (logical >= zone->start && logical < zone->end)
			return zone;
		spin_lock(&fs_info->reada_lock);
		kref_put(&zone->refcnt, reada_zone_release);
		spin_unlock(&fs_info->reada_lock);
	}

	cache = btrfs_lookup_block_group(fs_info, logical);
	if (!cache)
		return NULL;

	start = cache->key.objectid;
	end = start + cache->key.offset - 1;
	btrfs_put_block_group(cache);

	zone = kzalloc(sizeof(*zone), GFP_NOFS);
	if (!zone)
		return NULL;

	zone->start = start;
	zone->end = end;
	INIT_LIST_HEAD(&zone->list);
	spin_lock_init(&zone->lock);
	zone->locked = 0;
	kref_init(&zone->refcnt);
	zone->elems = 0;
	zone->device = dev;
	for (i = 0; i < bbio->num_stripes; ++i) {

		zone->devs[i] = bbio->stripes[i].dev;
	}
	zone->ndevs = bbio->num_stripes;

	spin_lock(&fs_info->reada_lock);
	ret = radix_tree_insert(&dev->reada_zones,
				(unsigned long)(zone->end >> PAGE_CACHE_SHIFT),
				zone);

	if (ret == -EEXIST) {
		kfree(zone);
		ret = radix_tree_gang_lookup(&dev->reada_zones, (void **)&zone,
					     logical >> PAGE_CACHE_SHIFT, 1);
		if (ret == 1)
			kref_get(&zone->refcnt);
	}
	spin_unlock(&fs_info->reada_lock);

	return zone;
}
