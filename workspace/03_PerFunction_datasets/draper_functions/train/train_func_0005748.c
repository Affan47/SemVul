btrfs_alloc_root(struct btrfs_fs_info *fs_info)
{
	struct btrfs_root *root = kzalloc(sizeof(*root), GFP_NOFS);
	if (root)
		root->fs_info = fs_info;
	return root;
}
