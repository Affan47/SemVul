ocfs2_truncate_inline(struct inode *inode, struct buffer_head *di_bh,
			  unsigned int start, unsigned int end, int trunc)
{
	int ret;
	unsigned int numbytes;
	handle_t *handle;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)di_bh->b_data;
	struct ocfs2_inline_data *idata = &di->id2.i_data;

	if (end > i_size_read(inode))
		end = i_size_read(inode);

	BUG_ON(start > end);

	if (!(OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) ||
	    !(le16_to_cpu(di->i_dyn_features) & OCFS2_INLINE_DATA_FL) ||
	    !ocfs2_supports_inline_data(osb)) {
		ocfs2_error(inode->i_sb,
			    "Inline data flags for inode %llu don't agree! Disk: 0x%x, Memory: 0x%x, Superblock: 0x%x\n",
			    (unsigned long long)OCFS2_I(inode)->ip_blkno,
			    le16_to_cpu(di->i_dyn_features),
			    OCFS2_I(inode)->ip_dyn_features,
			    osb->s_feature_incompat);
		ret = -EROFS;
		goto out;
	}

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	numbytes = end - start;
	memset(idata->id_data + start, 0, numbytes);


	if (trunc) {
		i_size_write(inode, start);
		di->i_size = cpu_to_le64(start);
	}

	inode->i_blocks = ocfs2_inode_sector_count(inode);
	inode->i_ctime = inode->i_mtime = CURRENT_TIME;

	di->i_ctime = di->i_mtime = cpu_to_le64(inode->i_ctime.tv_sec);
	di->i_ctime_nsec = di->i_mtime_nsec = cpu_to_le32(inode->i_ctime.tv_nsec);

	ocfs2_update_inode_fsync_trans(handle, inode, 1);
	ocfs2_journal_dirty(handle, di_bh);

out_commit:
	ocfs2_commit_trans(osb, handle);

out:
	return ret;
}
