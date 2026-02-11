btrfs_defrag_root(struct btrfs_root *root)
{
	struct btrfs_fs_info *info = root->fs_info;
	struct btrfs_trans_handle *trans;
	int ret;

	if (test_and_set_bit(BTRFS_ROOT_DEFRAG_RUNNING, &root->state))
		return 0;

	while (1) {
		trans = btrfs_start_transaction(root, 0);
		if (IS_ERR(trans))
			return PTR_ERR(trans);

		ret = btrfs_defrag_leaves(trans, root);

		btrfs_end_transaction(trans, root);
		btrfs_btree_balance_dirty(info->tree_root);
		cond_resched();

		if (btrfs_fs_closing(root->fs_info) || ret != -EAGAIN)
			break;

		if (btrfs_defrag_cancelled(root->fs_info)) {
			pr_debug("BTRFS: defrag_root cancelled\n");
			ret = -EAGAIN;
			break;
		}
	}
	clear_bit(BTRFS_ROOT_DEFRAG_RUNNING, &root->state);
	return ret;
}
