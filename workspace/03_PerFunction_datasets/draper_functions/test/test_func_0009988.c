btrfs_release_block_group(struct btrfs_block_group_cache *cache,
			 int delalloc)
{
	if (delalloc)
		up_read(&cache->data_rwsem);
	btrfs_put_block_group(cache);
}
