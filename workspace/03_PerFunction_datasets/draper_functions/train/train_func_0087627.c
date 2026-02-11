ocfs2_read_locked_inode(struct inode *inode,
				   struct ocfs2_find_inode_args *args)
{
	struct super_block *sb;
	struct ocfs2_super *osb;
	struct ocfs2_dinode *fe;
	struct buffer_head *bh = NULL;
	int status, can_lock;
	u32 generation = 0;

	status = -EINVAL;
	sb = inode->i_sb;
	osb = OCFS2_SB(sb);


	can_lock = !(args->fi_flags & OCFS2_FI_FLAG_SYSFILE)
		&& !(args->fi_flags & OCFS2_FI_FLAG_ORPHAN_RECOVERY)
		&& !ocfs2_mount_local(osb);

	trace_ocfs2_read_locked_inode(
		(unsigned long long)OCFS2_I(inode)->ip_blkno, can_lock);


	if (args->fi_flags & OCFS2_FI_FLAG_SYSFILE)
		generation = osb->fs_generation;

	ocfs2_inode_lock_res_init(&OCFS2_I(inode)->ip_inode_lockres,
				  OCFS2_LOCK_TYPE_META,
				  generation, inode);

	ocfs2_inode_lock_res_init(&OCFS2_I(inode)->ip_open_lockres,
				  OCFS2_LOCK_TYPE_OPEN,
				  0, inode);

	if (can_lock) {
		status = ocfs2_open_lock(inode);
		if (status) {
			make_bad_inode(inode);
			mlog_errno(status);
			return status;
		}
		status = ocfs2_inode_lock(inode, NULL, 0);
		if (status) {
			make_bad_inode(inode);
			mlog_errno(status);
			return status;
		}
	}

	if (args->fi_flags & OCFS2_FI_FLAG_ORPHAN_RECOVERY) {
		status = ocfs2_try_open_lock(inode, 0);
		if (status) {
			make_bad_inode(inode);
			return status;
		}
	}

	if (can_lock) {
		status = ocfs2_read_inode_block_full(inode, &bh,
						     OCFS2_BH_IGNORE_CACHE);
	} else {
		status = ocfs2_read_blocks_sync(osb, args->fi_blkno, 1, &bh);


		if (!status && !buffer_jbd(bh))
			status = ocfs2_validate_inode_block(osb->sb, bh);
	}
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = -EINVAL;
	fe = (struct ocfs2_dinode *) bh->b_data;


	mlog_bug_on_msg(!!(fe->i_flags & cpu_to_le32(OCFS2_SYSTEM_FL)) !=
			!!(args->fi_flags & OCFS2_FI_FLAG_SYSFILE),
			"Inode %llu: system file state is ambigous\n",
			(unsigned long long)args->fi_blkno);

	if (S_ISCHR(le16_to_cpu(fe->i_mode)) ||
	    S_ISBLK(le16_to_cpu(fe->i_mode)))
		inode->i_rdev = huge_decode_dev(le64_to_cpu(fe->id1.dev1.i_rdev));

	ocfs2_populate_inode(inode, fe, 0);

	BUG_ON(args->fi_blkno != le64_to_cpu(fe->i_blkno));

	status = 0;

bail:
	if (can_lock)
		ocfs2_inode_unlock(inode, 0);

	if (status < 0)
		make_bad_inode(inode);

	brelse(bh);

	return status;
}
