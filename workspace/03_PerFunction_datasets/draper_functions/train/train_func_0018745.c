__ocfs2_resv_discard(struct ocfs2_reservation_map *resmap,
				 struct ocfs2_alloc_reservation *resv)
{
	assert_spin_locked(&resv_lock);

	__ocfs2_resv_trunc(resv);


	resv->r_last_len = resv->r_last_start = 0;

	ocfs2_resv_remove(resmap, resv);
}
