debugfs_write_file_bool(struct file *file, const char __user *user_buf,
				size_t count, loff_t *ppos)
{
	char buf[32];
	size_t buf_size;
	bool bv;
	bool *val = file->private_data;

	buf_size = min(count, (sizeof(buf)-1));
	if (copy_from_user(buf, user_buf, buf_size))
		return -EFAULT;

	buf[buf_size] = '\0';
	if (strtobool(buf, &bv) == 0)
		*val = bv;

	return count;
}
