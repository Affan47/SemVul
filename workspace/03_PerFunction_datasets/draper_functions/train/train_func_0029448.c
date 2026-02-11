btrfs_get_alloc_profile(struct btrfs_root *root, int data)
{
	u64 flags;
	u64 ret;

	if (data)
		flags = BTRFS_BLOCK_GROUP_DATA;
	else if (root == root->fs_info->chunk_root)
		flags = BTRFS_BLOCK_GROUP_SYSTEM;
	else
		flags = BTRFS_BLOCK_GROUP_METADATA;

	ret = get_alloc_profile(root, flags);
	return ret;
}
