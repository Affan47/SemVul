ocfs2_find_smallest_chain(struct ocfs2_chain_list *cl)
{
	u16 curr, best;

	best = curr = 0;
	while (curr < le16_to_cpu(cl->cl_count)) {
		if (le32_to_cpu(cl->cl_recs[best].c_total) >
		    le32_to_cpu(cl->cl_recs[curr].c_total))
			best = curr;
		curr++;
	}
	return best;
}
