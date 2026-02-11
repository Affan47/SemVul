vfs_test_lock(struct file *filp, struct file_lock *fl)
{
	if (filp->f_op->lock)
		return filp->f_op->lock(filp, F_GETLK, fl);
	posix_test_lock(filp, fl);
	return 0;
}
