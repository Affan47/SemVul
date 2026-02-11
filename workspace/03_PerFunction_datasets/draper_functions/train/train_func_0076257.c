ocfs2_clear_inode(struct inode *inode)
{
	int status;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	clear_inode(inode);
	trace_ocfs2_clear_inode((unsigned long long)oi->ip_blkno,
				inode->i_nlink);

	mlog_bug_on_msg(OCFS2_SB(inode->i_sb) == NULL,
			"Inode=%lu\n", inode->i_ino);

	dquot_drop(inode);


	ocfs2_open_unlock(inode);


	ocfs2_mark_lockres_freeing(osb, &oi->ip_rw_lockres);
	ocfs2_mark_lockres_freeing(osb, &oi->ip_inode_lockres);
	ocfs2_mark_lockres_freeing(osb, &oi->ip_open_lockres);

	ocfs2_resv_discard(&OCFS2_SB(inode->i_sb)->osb_la_resmap,
			   &oi->ip_la_data_resv);
	ocfs2_resv_init_once(&oi->ip_la_data_resv);


	if (!(OCFS2_I(inode)->ip_flags & OCFS2_INODE_DELETED))
		ocfs2_checkpoint_inode(inode);

	mlog_bug_on_msg(!list_empty(&oi->ip_io_markers),
			"Clear inode of %llu, inode has io markers\n",
			(unsigned long long)oi->ip_blkno);

	ocfs2_extent_map_trunc(inode, 0);

	status = ocfs2_drop_inode_locks(inode);
	if (status < 0)
		mlog_errno(status);

	ocfs2_lock_res_free(&oi->ip_rw_lockres);
	ocfs2_lock_res_free(&oi->ip_inode_lockres);
	ocfs2_lock_res_free(&oi->ip_open_lockres);

	ocfs2_metadata_cache_exit(INODE_CACHE(inode));

	mlog_bug_on_msg(INODE_CACHE(inode)->ci_num_cached,
			"Clear inode of %llu, inode has %u cache items\n",
			(unsigned long long)oi->ip_blkno,
			INODE_CACHE(inode)->ci_num_cached);

	mlog_bug_on_msg(!(INODE_CACHE(inode)->ci_flags & OCFS2_CACHE_FL_INLINE),
			"Clear inode of %llu, inode has a bad flag\n",
			(unsigned long long)oi->ip_blkno);

	mlog_bug_on_msg(spin_is_locked(&oi->ip_lock),
			"Clear inode of %llu, inode is locked\n",
			(unsigned long long)oi->ip_blkno);

	mlog_bug_on_msg(!mutex_trylock(&oi->ip_io_mutex),
			"Clear inode of %llu, io_mutex is locked\n",
			(unsigned long long)oi->ip_blkno);
	mutex_unlock(&oi->ip_io_mutex);


	mlog_bug_on_msg(!down_write_trylock(&oi->ip_alloc_sem),
			"Clear inode of %llu, alloc_sem is locked\n",
			(unsigned long long)oi->ip_blkno);
	up_write(&oi->ip_alloc_sem);

	mlog_bug_on_msg(oi->ip_open_count,
			"Clear inode of %llu has open count %d\n",
			(unsigned long long)oi->ip_blkno, oi->ip_open_count);


	oi->ip_flags = 0;
	oi->ip_dir_start_lookup = 0;
	oi->ip_blkno = 0ULL;


	jbd2_journal_release_jbd_inode(OCFS2_SB(inode->i_sb)->journal->j_journal,
				       &oi->ip_jinode);
}
