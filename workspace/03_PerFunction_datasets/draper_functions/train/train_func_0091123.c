ocfs2_find_entry_id(const char *name,
					       int namelen,
					       struct inode *dir,
					       struct ocfs2_dir_entry **res_dir)
{
	int ret, found;
	struct buffer_head *di_bh = NULL;
	struct ocfs2_dinode *di;
	struct ocfs2_inline_data *data;

	ret = ocfs2_read_inode_block(dir, &di_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	di = (struct ocfs2_dinode *)di_bh->b_data;
	data = &di->id2.i_data;

	found = ocfs2_search_dirblock(di_bh, dir, name, namelen, 0,
				      data->id_data, i_size_read(dir), res_dir);
	if (found == 1)
		return di_bh;

	brelse(di_bh);
out:
	return NULL;
}
