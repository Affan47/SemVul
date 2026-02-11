parq_upload_insert_relative(struct parq_ul_queued *puq)
{
	parq_ul_queued_check(puq);

	g_assert(!(puq->flags & PARQ_UL_FROZEN));

	puq->relative_position = 0;
	hash_list_insert_sorted(puq->queue->by_rel_pos, puq, parq_ul_rel_pos_cmp);
}
