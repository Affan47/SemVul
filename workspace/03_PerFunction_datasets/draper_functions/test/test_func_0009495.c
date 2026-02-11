ocfs2_leftmost_rec_contains(struct ocfs2_extent_list *el, u32 cpos)
{
	int next_free = le16_to_cpu(el->l_next_free_rec);
	unsigned int range;
	struct ocfs2_extent_rec *rec;

	if (next_free == 0)
		return 0;

	rec = &el->l_recs[0];
	if (ocfs2_is_empty_extent(rec)) {

		if (next_free == 1)
			return 0;
		rec = &el->l_recs[1];
	}

	range = le32_to_cpu(rec->e_cpos) + ocfs2_rec_clusters(el, rec);
	if (cpos >= le32_to_cpu(rec->e_cpos) && cpos < range)
		return 1;
	return 0;
}
