f2fs_do_collapse(struct inode *inode, pgoff_t start, pgoff_t end)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	pgoff_t nrpages = (i_size_read(inode) + PAGE_SIZE - 1) / PAGE_SIZE;
	int ret = 0;

	for (; end < nrpages; start++, end++) {
		f2fs_balance_fs(sbi);
		f2fs_lock_op(sbi);
		ret = __exchange_data_block(inode, end, start, true);
		f2fs_unlock_op(sbi);
		if (ret)
			break;
	}
	return ret;
}
