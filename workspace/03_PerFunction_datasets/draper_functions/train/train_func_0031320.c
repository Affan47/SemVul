bfad_debugfs_release_fwtrc(struct inode *inode, struct file *file)
{
	struct bfad_debug_info *fw_debug = file->private_data;

	if (!fw_debug)
		return 0;

	if (fw_debug->debug_buffer)
		vfree(fw_debug->debug_buffer);

	file->private_data = NULL;
	kfree(fw_debug);
	return 0;
}
