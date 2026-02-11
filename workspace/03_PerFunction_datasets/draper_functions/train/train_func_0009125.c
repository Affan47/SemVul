add_pinned_bytes(struct btrfs_fs_info *fs_info, u64 num_bytes,
			     u64 owner, u64 root_objectid)
{
	struct btrfs_space_info *space_info;
	u64 flags;

	if (owner < BTRFS_FIRST_FREE_OBJECTID) {
		if (root_objectid == BTRFS_CHUNK_TREE_OBJECTID)
			flags = BTRFS_BLOCK_GROUP_SYSTEM;
		else
			flags = BTRFS_BLOCK_GROUP_METADATA;
	} else {
		flags = BTRFS_BLOCK_GROUP_DATA;
	}

	space_info = __find_space_info(fs_info, flags);
	BUG_ON(!space_info);
	percpu_counter_add(&space_info->total_bytes_pinned, num_bytes);
}
