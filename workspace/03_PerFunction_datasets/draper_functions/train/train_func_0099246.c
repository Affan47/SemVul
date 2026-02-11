_ocfs2_free_suballoc_bits(handle_t *handle,
				     struct inode *alloc_inode,
				     struct buffer_head *alloc_bh,
				     unsigned int start_bit,
				     u64 bg_blkno,
				     unsigned int count,
				     void (*undo_fn)(unsigned int bit,
						     unsigned long *bitmap))
{
	int status = 0;
	u32 tmp_used;
	struct ocfs2_dinode *fe = (struct ocfs2_dinode *) alloc_bh->b_data;
	struct ocfs2_chain_list *cl = &fe->id2.i_chain;
	struct buffer_head *group_bh = NULL;
	struct ocfs2_group_desc *group;


	BUG_ON(!OCFS2_IS_VALID_DINODE(fe));
	BUG_ON((count + start_bit) > ocfs2_bits_per_group(cl));

	trace_ocfs2_free_suballoc_bits(
		(unsigned long long)OCFS2_I(alloc_inode)->ip_blkno,
		(unsigned long long)bg_blkno,
		start_bit, count);

	status = ocfs2_read_group_descriptor(alloc_inode, fe, bg_blkno,
					     &group_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}
	group = (struct ocfs2_group_desc *) group_bh->b_data;

	BUG_ON((count + start_bit) > le16_to_cpu(group->bg_bits));

	status = ocfs2_block_group_clear_bits(handle, alloc_inode,
					      group, group_bh,
					      start_bit, count, undo_fn);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = ocfs2_journal_access_di(handle, INODE_CACHE(alloc_inode),
					 alloc_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		ocfs2_block_group_set_bits(handle, alloc_inode, group, group_bh,
				start_bit, count);
		goto bail;
	}

	le32_add_cpu(&cl->cl_recs[le16_to_cpu(group->bg_chain)].c_free,
		     count);
	tmp_used = le32_to_cpu(fe->id1.bitmap1.i_used);
	fe->id1.bitmap1.i_used = cpu_to_le32(tmp_used - count);
	ocfs2_journal_dirty(handle, alloc_bh);

bail:
	brelse(group_bh);

	if (status)
		mlog_errno(status);
	return status;
}
