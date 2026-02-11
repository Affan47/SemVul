ocfs2_resv_remove(struct ocfs2_reservation_map *resmap,
			      struct ocfs2_alloc_reservation *resv)
{
	if (resv->r_flags & OCFS2_RESV_FLAG_INUSE) {
		list_del_init(&resv->r_lru);
		rb_erase(&resv->r_node, &resmap->m_reservations);
		resv->r_flags &= ~OCFS2_RESV_FLAG_INUSE;
	}
}
