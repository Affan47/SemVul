check_conflicting_open(const struct dentry *dentry, const long arg, int flags)
{
	int ret = 0;
	struct inode *inode = dentry->d_inode;

	if (flags & FL_LAYOUT)
		return 0;

	if ((arg == F_RDLCK) && (atomic_read(&inode->i_writecount) > 0))
		return -EAGAIN;

	if ((arg == F_WRLCK) && ((d_count(dentry) > 1) ||
	    (atomic_read(&inode->i_count) > 1)))
		ret = -EAGAIN;

	return ret;
}
