ocfs2_claim_new_inode_at_loc(handle_t *handle,
				 struct inode *dir,
				 struct ocfs2_alloc_context *ac,
				 u64 *suballoc_loc,
				 u16 *suballoc_bit,
				 u64 di_blkno)
{
	int ret;
	u16 chain;
	struct ocfs2_suballoc_result *res = ac->ac_find_loc_priv;
	struct buffer_head *bg_bh = NULL;
	struct ocfs2_group_desc *bg;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *) ac->ac_bh->b_data;


	BUG_ON(res->sr_blkno != di_blkno);

	ret = ocfs2_read_group_descriptor(ac->ac_inode, di,
					  res->sr_bg_stable_blkno, &bg_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	bg = (struct ocfs2_group_desc *) bg_bh->b_data;
	chain = le16_to_cpu(bg->bg_chain);

	ret = ocfs2_alloc_dinode_update_counts(ac->ac_inode, handle,
					       ac->ac_bh, res->sr_bits,
					       chain);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_block_group_set_bits(handle,
					 ac->ac_inode,
					 bg,
					 bg_bh,
					 res->sr_bit_offset,
					 res->sr_bits);
	if (ret < 0) {
		ocfs2_rollback_alloc_dinode_counts(ac->ac_inode,
					       ac->ac_bh, res->sr_bits, chain);
		mlog_errno(ret);
		goto out;
	}

	trace_ocfs2_claim_new_inode_at_loc((unsigned long long)di_blkno,
					   res->sr_bits);

	atomic_inc(&OCFS2_SB(ac->ac_inode->i_sb)->alloc_stats.bg_allocs);

	BUG_ON(res->sr_bits != 1);

	*suballoc_loc = res->sr_bg_blkno;
	*suballoc_bit = res->sr_bit_offset;
	ac->ac_bits_given++;
	ocfs2_save_inode_ac_group(dir, ac);

out:
	brelse(bg_bh);

	return ret;
}
