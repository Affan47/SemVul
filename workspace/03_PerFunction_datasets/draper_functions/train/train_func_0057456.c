add_root_to_dirty_list(struct btrfs_root *root)
{
	if (test_bit(BTRFS_ROOT_DIRTY, &root->state) ||
	    !test_bit(BTRFS_ROOT_TRACK_DIRTY, &root->state))
		return;

	spin_lock(&root->fs_info->trans_lock);
	if (!test_and_set_bit(BTRFS_ROOT_DIRTY, &root->state)) {

		if (root->objectid == BTRFS_EXTENT_TREE_OBJECTID)
			list_move_tail(&root->dirty_list,
				       &root->fs_info->dirty_cowonly_roots);
		else
			list_move(&root->dirty_list,
				  &root->fs_info->dirty_cowonly_roots);
	}
	spin_unlock(&root->fs_info->trans_lock);
}
