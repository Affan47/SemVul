ocfs2_truncate_for_delete(struct ocfs2_super *osb,
				     struct inode *inode,
				     struct buffer_head *fe_bh)
{
	int status = 0;
	struct ocfs2_dinode *fe;
	handle_t *handle = NULL;

	fe = (struct ocfs2_dinode *) fe_bh->b_data;


	if (fe->i_clusters) {
		if (ocfs2_should_order_data(inode))
			ocfs2_begin_ordered_truncate(inode, 0);

		handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
		if (IS_ERR(handle)) {
			status = PTR_ERR(handle);
			handle = NULL;
			mlog_errno(status);
			goto out;
		}

		status = ocfs2_journal_access_di(handle, INODE_CACHE(inode),
						 fe_bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		if (status < 0) {
			mlog_errno(status);
			goto out;
		}

		i_size_write(inode, 0);

		status = ocfs2_mark_inode_dirty(handle, inode, fe_bh);
		if (status < 0) {
			mlog_errno(status);
			goto out;
		}

		ocfs2_commit_trans(osb, handle);
		handle = NULL;

		status = ocfs2_commit_truncate(osb, inode, fe_bh);
		if (status < 0) {
			mlog_errno(status);
			goto out;
		}
	}

out:
	if (handle)
		ocfs2_commit_trans(osb, handle);
	return status;
}
