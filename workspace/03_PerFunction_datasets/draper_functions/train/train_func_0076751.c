ocfs2_bg_discontig_add_extent(struct ocfs2_super *osb,
					  struct ocfs2_group_desc *bg,
					  struct ocfs2_chain_list *cl,
					  u64 p_blkno, unsigned int clusters)
{
	struct ocfs2_extent_list *el = &bg->bg_list;
	struct ocfs2_extent_rec *rec;

	BUG_ON(!ocfs2_supports_discontig_bg(osb));
	if (!el->l_next_free_rec)
		el->l_count = cpu_to_le16(ocfs2_extent_recs_per_gd(osb->sb));
	rec = &el->l_recs[le16_to_cpu(el->l_next_free_rec)];
	rec->e_blkno = cpu_to_le64(p_blkno);
	rec->e_cpos = cpu_to_le32(le16_to_cpu(bg->bg_bits) /
				  le16_to_cpu(cl->cl_bpc));
	rec->e_leaf_clusters = cpu_to_le16(clusters);
	le16_add_cpu(&bg->bg_bits, clusters * le16_to_cpu(cl->cl_bpc));
	le16_add_cpu(&bg->bg_free_bits_count,
		     clusters * le16_to_cpu(cl->cl_bpc));
	le16_add_cpu(&el->l_next_free_rec, 1);
}
