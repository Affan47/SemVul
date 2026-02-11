f2fs_sync_file(struct file *file, loff_t start, loff_t end, int datasync)
{
	struct inode *inode = file->f_mapping->host;
	struct f2fs_inode_info *fi = F2FS_I(inode);
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	nid_t ino = inode->i_ino;
	int ret = 0;
	bool need_cp = false;
	struct writeback_control wbc = {
		.sync_mode = WB_SYNC_ALL,
		.nr_to_write = LONG_MAX,
		.for_reclaim = 0,
	};

	if (unlikely(f2fs_readonly(inode->i_sb)))
		return 0;

	trace_f2fs_sync_file_enter(inode);


	if (get_dirty_pages(inode) <= SM_I(sbi)->min_fsync_blocks)
		set_inode_flag(fi, FI_NEED_IPU);
	ret = filemap_write_and_wait_range(inode->i_mapping, start, end);
	clear_inode_flag(fi, FI_NEED_IPU);

	if (ret) {
		trace_f2fs_sync_file_exit(inode, need_cp, datasync, ret);
		return ret;
	}


	if (!datasync) {
		f2fs_write_inode(inode, NULL);
		goto go_write;
	}


	if (!is_inode_flag_set(fi, FI_APPEND_WRITE) &&
			!exist_written_data(sbi, ino, APPEND_INO)) {


		if (need_inode_page_update(sbi, ino))
			goto go_write;

		if (is_inode_flag_set(fi, FI_UPDATE_WRITE) ||
				exist_written_data(sbi, ino, UPDATE_INO))
			goto flush_out;
		goto out;
	}
go_write:

	f2fs_balance_fs(sbi);


	down_read(&fi->i_sem);
	need_cp = need_do_checkpoint(inode);
	up_read(&fi->i_sem);

	if (need_cp) {

		ret = f2fs_sync_fs(inode->i_sb, 1);


		try_to_fix_pino(inode);
		clear_inode_flag(fi, FI_APPEND_WRITE);
		clear_inode_flag(fi, FI_UPDATE_WRITE);
		goto out;
	}
sync_nodes:
	sync_node_pages(sbi, ino, &wbc);


	if (unlikely(f2fs_cp_error(sbi)))
		goto out;

	if (need_inode_block_update(sbi, ino)) {
		mark_inode_dirty_sync(inode);
		f2fs_write_inode(inode, NULL);
		goto sync_nodes;
	}

	ret = wait_on_node_pages_writeback(sbi, ino);
	if (ret)
		goto out;


	remove_dirty_inode(sbi, ino, APPEND_INO);
	clear_inode_flag(fi, FI_APPEND_WRITE);
flush_out:
	remove_dirty_inode(sbi, ino, UPDATE_INO);
	clear_inode_flag(fi, FI_UPDATE_WRITE);
	ret = f2fs_issue_flush(sbi);
out:
	trace_f2fs_sync_file_exit(inode, need_cp, datasync, ret);
	f2fs_trace_ios(NULL, 1);
	return ret;
}
