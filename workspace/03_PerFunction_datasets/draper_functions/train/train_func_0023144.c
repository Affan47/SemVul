coda_permission(struct inode *inode, int mask)
{
	int error;

	if (mask & MAY_NOT_BLOCK)
		return -ECHILD;

	mask &= MAY_READ | MAY_WRITE | MAY_EXEC;

	if (!mask)
		return 0;

	if ((mask & MAY_EXEC) && !execute_ok(inode))
		return -EACCES;

	if (coda_cache_check(inode, mask))
		return 0;

	error = venus_access(inode->i_sb, coda_i2f(inode), mask);

	if (!error)
		coda_cache_enter(inode, mask);

	return error;
}
