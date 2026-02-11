btrfs_add_dead_root(struct btrfs_root *root)
{
	spin_lock(&root->fs_info->trans_lock);
	if (list_empty(&root->root_list))
		list_add_tail(&root->root_list, &root->fs_info->dead_roots);
	spin_unlock(&root->fs_info->trans_lock);
}
