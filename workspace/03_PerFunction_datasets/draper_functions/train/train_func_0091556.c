xlog_recover_inode_ra_pass2(
	struct xlog                     *log,
	struct xlog_recover_item        *item)
{
	struct xfs_inode_log_format	ilf_buf;
	struct xfs_inode_log_format	*ilfp;
	struct xfs_mount		*mp = log->l_mp;
	int			error;

	if (item->ri_buf[0].i_len == sizeof(struct xfs_inode_log_format)) {
		ilfp = item->ri_buf[0].i_addr;
	} else {
		ilfp = &ilf_buf;
		memset(ilfp, 0, sizeof(*ilfp));
		error = xfs_inode_item_format_convert(&item->ri_buf[0], ilfp);
		if (error)
			return;
	}

	if (xlog_peek_buffer_cancelled(log, ilfp->ilf_blkno, ilfp->ilf_len, 0))
		return;

	xfs_buf_readahead(mp->m_ddev_targp, ilfp->ilf_blkno,
				ilfp->ilf_len, &xfs_inode_buf_ra_ops);
}
