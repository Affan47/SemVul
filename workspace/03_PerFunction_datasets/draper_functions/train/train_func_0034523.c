ocfs2_search_for_hole_index(struct ocfs2_extent_list *el,
				       u32 v_cluster)
{
	int i;
	struct ocfs2_extent_rec *rec;

	for(i = 0; i < le16_to_cpu(el->l_next_free_rec); i++) {
		rec = &el->l_recs[i];

		if (v_cluster < le32_to_cpu(rec->e_cpos))
			break;
	}

	return i;
}
