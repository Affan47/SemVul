btrfs_put_block_group_cache(struct btrfs_fs_info *info)
{
	struct btrfs_block_group_cache *block_group;
	u64 last = 0;

	while (1) {
		struct inode *inode;

		block_group = btrfs_lookup_first_block_group(info, last);
		while (block_group) {
			spin_lock(&block_group->lock);
			if (block_group->iref)
				break;
			spin_unlock(&block_group->lock);
			block_group = next_block_group(info->tree_root,
						       block_group);
		}
		if (!block_group) {
			if (last == 0)
				break;
			last = 0;
			continue;
		}

		inode = block_group->inode;
		block_group->iref = 0;
		block_group->inode = NULL;
		spin_unlock(&block_group->lock);
		iput(inode);
		last = block_group->key.objectid + block_group->key.offset;
		btrfs_put_block_group(block_group);
	}
}
