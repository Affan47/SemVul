f2fs_ioc_abort_volatile_write(struct file *filp)
{
	struct inode *inode = file_inode(filp);
	int ret;

	if (!inode_owner_or_capable(inode))
		return -EACCES;

	ret = mnt_want_write_file(filp);
	if (ret)
		return ret;

	f2fs_balance_fs(F2FS_I_SB(inode));

	clear_inode_flag(F2FS_I(inode), FI_ATOMIC_FILE);
	clear_inode_flag(F2FS_I(inode), FI_VOLATILE_FILE);
	commit_inmem_pages(inode, true);

	mnt_drop_write_file(filp);
	return ret;
}
