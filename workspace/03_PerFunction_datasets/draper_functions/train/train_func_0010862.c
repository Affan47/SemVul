ocfs2_bg_discontig_fix_result(struct ocfs2_alloc_context *ac,
					  struct ocfs2_group_desc *bg,
					  struct ocfs2_suballoc_result *res)
{
	int i;
	u64 bg_blkno = res->sr_bg_blkno;
	struct ocfs2_extent_rec *rec;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)ac->ac_bh->b_data;
	struct ocfs2_chain_list *cl = &di->id2.i_chain;

	if (ocfs2_is_cluster_bitmap(ac->ac_inode)) {
		res->sr_blkno = 0;
		return;
	}

	res->sr_blkno = res->sr_bg_blkno + res->sr_bit_offset;
	res->sr_bg_blkno = 0;
	if (!ocfs2_supports_discontig_bg(OCFS2_SB(ac->ac_inode->i_sb)) ||
	    !bg->bg_list.l_next_free_rec)
		return;

	for (i = 0; i < le16_to_cpu(bg->bg_list.l_next_free_rec); i++) {
		rec = &bg->bg_list.l_recs[i];
		if (ocfs2_bg_discontig_fix_by_rec(res, rec, cl)) {
			res->sr_bg_blkno = bg_blkno;
			break;
		}
	}
}
