efivarfs_ioc_getxflags(struct file *file, void __user *arg)
{
	struct inode *inode = file->f_mapping->host;
	unsigned int i_flags;
	unsigned int flags = 0;

	i_flags = inode->i_flags;
	if (i_flags & S_IMMUTABLE)
		flags |= FS_IMMUTABLE_FL;

	if (copy_to_user(arg, &flags, sizeof(flags)))
		return -EFAULT;
	return 0;
}
