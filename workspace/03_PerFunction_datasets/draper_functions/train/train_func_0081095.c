ocfs2_set_inode_attr(struct inode *inode, unsigned flags,
				unsigned mask)
{
	struct ocfs2_inode_info *ocfs2_inode = OCFS2_I(inode);
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	handle_t *handle = NULL;
	struct buffer_head *bh = NULL;
	unsigned oldflags;
	int status;

	mutex_lock(&inode->i_mutex);

	status = ocfs2_inode_lock(inode, &bh, 1);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = -EACCES;
	if (!inode_owner_or_capable(inode))
		goto bail_unlock;

	if (!S_ISDIR(inode->i_mode))
		flags &= ~OCFS2_DIRSYNC_FL;

	oldflags = ocfs2_inode->ip_attr;
	flags = flags & mask;
	flags |= oldflags & ~mask;


	status = -EPERM;
	if ((oldflags & OCFS2_IMMUTABLE_FL) || ((flags ^ oldflags) &
		(OCFS2_APPEND_FL | OCFS2_IMMUTABLE_FL))) {
		if (!capable(CAP_LINUX_IMMUTABLE))
			goto bail_unlock;
	}

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		mlog_errno(status);
		goto bail_unlock;
	}

	ocfs2_inode->ip_attr = flags;
	ocfs2_set_inode_flags(inode);

	status = ocfs2_mark_inode_dirty(handle, inode, bh);
	if (status < 0)
		mlog_errno(status);

	ocfs2_commit_trans(osb, handle);

bail_unlock:
	ocfs2_inode_unlock(inode, 1);
bail:
	mutex_unlock(&inode->i_mutex);

	brelse(bh);

	return status;
}
