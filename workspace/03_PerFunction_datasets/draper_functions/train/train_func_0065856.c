exclude_super_stripes(struct btrfs_root *root,
				 struct btrfs_block_group_cache *cache)
{
	u64 bytenr;
	u64 *logical;
	int stripe_len;
	int i, nr, ret;

	if (cache->key.objectid < BTRFS_SUPER_INFO_OFFSET) {
		stripe_len = BTRFS_SUPER_INFO_OFFSET - cache->key.objectid;
		cache->bytes_super += stripe_len;
		ret = add_excluded_extent(root, cache->key.objectid,
					  stripe_len);
		if (ret)
			return ret;
	}

	for (i = 0; i < BTRFS_SUPER_MIRROR_MAX; i++) {
		bytenr = btrfs_sb_offset(i);
		ret = btrfs_rmap_block(&root->fs_info->mapping_tree,
				       cache->key.objectid, bytenr,
				       0, &logical, &nr, &stripe_len);
		if (ret)
			return ret;

		while (nr--) {
			u64 start, len;

			if (logical[nr] > cache->key.objectid +
			    cache->key.offset)
				continue;

			if (logical[nr] + stripe_len <= cache->key.objectid)
				continue;

			start = logical[nr];
			if (start < cache->key.objectid) {
				start = cache->key.objectid;
				len = (logical[nr] + stripe_len) - start;
			} else {
				len = min_t(u64, stripe_len,
					    cache->key.objectid +
					    cache->key.offset - start);
			}

			cache->bytes_super += len;
			ret = add_excluded_extent(root, start, len);
			if (ret) {
				kfree(logical);
				return ret;
			}
		}

		kfree(logical);
	}
	return 0;
}
