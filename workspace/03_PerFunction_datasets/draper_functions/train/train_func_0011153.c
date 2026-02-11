join_running_log_trans(struct btrfs_root *root)
{
	int ret = -ENOENT;

	smp_mb();
	if (!root->log_root)
		return -ENOENT;

	mutex_lock(&root->log_mutex);
	if (root->log_root) {
		ret = 0;
		atomic_inc(&root->log_writers);
	}
	mutex_unlock(&root->log_mutex);
	return ret;
}
