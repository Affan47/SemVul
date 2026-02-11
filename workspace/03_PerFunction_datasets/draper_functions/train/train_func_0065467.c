ocfs2_resmap_claimed_bits(struct ocfs2_reservation_map *resmap,
			       struct ocfs2_alloc_reservation *resv,
			       u32 cstart, u32 clen)
{
	unsigned int cend = cstart + clen - 1;

	if (resmap == NULL || ocfs2_resmap_disabled(resmap))
		return;

	if (resv == NULL)
		return;

	BUG_ON(cstart != resv->r_start);

	spin_lock(&resv_lock);

	trace_ocfs2_resmap_claimed_bits_begin(cstart, cend, clen, resv->r_start,
					      ocfs2_resv_end(resv), resv->r_len,
					      resv->r_last_start,
					      resv->r_last_len);

	BUG_ON(cstart < resv->r_start);
	BUG_ON(cstart > ocfs2_resv_end(resv));
	BUG_ON(cend > ocfs2_resv_end(resv));

	ocfs2_adjust_resv_from_alloc(resmap, resv, cstart, cend);
	resv->r_last_start = cstart;
	resv->r_last_len = clen;


	if (!ocfs2_resv_empty(resv))
		ocfs2_resv_mark_lru(resmap, resv);

	trace_ocfs2_resmap_claimed_bits_end(resv->r_start, ocfs2_resv_end(resv),
					    resv->r_len, resv->r_last_start,
					    resv->r_last_len);

	ocfs2_check_resmap(resmap);

	spin_unlock(&resv_lock);
}
