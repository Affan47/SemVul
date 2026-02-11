bnad_debugfs_release(struct inode *inode, struct file *file)
{
	struct bnad_debug_info *debug = file->private_data;

	if (!debug)
		return 0;

	file->private_data = NULL;
	kfree(debug);
	return 0;
}
