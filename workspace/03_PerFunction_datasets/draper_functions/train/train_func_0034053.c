ocfs2_info_scan_inode_alloc(struct ocfs2_super *osb,
				       struct inode *inode_alloc, u64 blkno,
				       struct ocfs2_info_freeinode *fi,
				       u32 slot)
{
	int status = 0, unlock = 0;

	struct buffer_head *bh = NULL;
	struct ocfs2_dinode *dinode_alloc = NULL;

	if (inode_alloc)
		mutex_lock(&inode_alloc->i_mutex);

	if (o2info_coherent(&fi->ifi_req)) {
		status = ocfs2_inode_lock(inode_alloc, &bh, 0);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
		unlock = 1;
	} else {
		status = ocfs2_read_blocks_sync(osb, blkno, 1, &bh);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
	}

	dinode_alloc = (struct ocfs2_dinode *)bh->b_data;

	fi->ifi_stat[slot].lfi_total =
		le32_to_cpu(dinode_alloc->id1.bitmap1.i_total);
	fi->ifi_stat[slot].lfi_free =
		le32_to_cpu(dinode_alloc->id1.bitmap1.i_total) -
		le32_to_cpu(dinode_alloc->id1.bitmap1.i_used);

bail:
	if (unlock)
		ocfs2_inode_unlock(inode_alloc, 0);

	if (inode_alloc)
		mutex_unlock(&inode_alloc->i_mutex);

	brelse(bh);

	return status;
}
