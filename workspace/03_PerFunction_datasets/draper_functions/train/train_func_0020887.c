btrfs_free_log(struct btrfs_trans_handle *trans, struct btrfs_root *root)
{
	if (root->log_root) {
		free_log_tree(trans, root->log_root);
		root->log_root = NULL;
	}
	return 0;
}
