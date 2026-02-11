update_log_root(struct btrfs_trans_handle *trans,
			   struct btrfs_root *log)
{
	int ret;

	if (log->log_transid == 1) {

		ret = btrfs_insert_root(trans, log->fs_info->log_root_tree,
				&log->root_key, &log->root_item);
	} else {
		ret = btrfs_update_root(trans, log->fs_info->log_root_tree,
				&log->root_key, &log->root_item);
	}
	return ret;
}
