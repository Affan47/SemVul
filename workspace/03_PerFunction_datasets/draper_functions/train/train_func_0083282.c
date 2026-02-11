ocfs2_reflink(struct dentry *old_dentry, struct inode *dir,
			 struct dentry *new_dentry, bool preserve)
{
	int error;
	struct inode *inode = d_inode(old_dentry);
	struct buffer_head *old_bh = NULL;
	struct inode *new_orphan_inode = NULL;

	if (!ocfs2_refcount_tree(OCFS2_SB(inode->i_sb)))
		return -EOPNOTSUPP;


	error = ocfs2_create_inode_in_orphan(dir, inode->i_mode,
					     &new_orphan_inode);
	if (error) {
		mlog_errno(error);
		goto out;
	}

	error = ocfs2_rw_lock(inode, 1);
	if (error) {
		mlog_errno(error);
		goto out;
	}

	error = ocfs2_inode_lock(inode, &old_bh, 1);
	if (error) {
		mlog_errno(error);
		ocfs2_rw_unlock(inode, 1);
		goto out;
	}

	down_write(&OCFS2_I(inode)->ip_xattr_sem);
	down_write(&OCFS2_I(inode)->ip_alloc_sem);
	error = __ocfs2_reflink(old_dentry, old_bh,
				new_orphan_inode, preserve);
	up_write(&OCFS2_I(inode)->ip_alloc_sem);
	up_write(&OCFS2_I(inode)->ip_xattr_sem);

	ocfs2_inode_unlock(inode, 1);
	ocfs2_rw_unlock(inode, 1);
	brelse(old_bh);

	if (error) {
		mlog_errno(error);
		goto out;
	}


	if (!preserve) {
		error = ocfs2_init_security_and_acl(dir, new_orphan_inode,
						    &new_dentry->d_name);
		if (error)
			mlog_errno(error);
	}
out:
	if (!error) {
		error = ocfs2_mv_orphaned_inode_to_new(dir, new_orphan_inode,
						       new_dentry);
		if (error)
			mlog_errno(error);
	}

	if (new_orphan_inode) {


		ocfs2_open_unlock(new_orphan_inode);
		if (error)
			iput(new_orphan_inode);
	}

	return error;
}
