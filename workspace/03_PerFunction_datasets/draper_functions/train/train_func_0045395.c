parq_ul_dump_earlier(struct parq_ul_queued *item)
{
	struct parq_ul_queue *q;
	hash_list_iter_t *iter;
	unsigned old_relative = 0;

	parq_ul_queued_check(item);

	q = item->queue;
	parq_ul_queue_check(q);

	iter = hash_list_iterator(q->by_rel_pos);

	while (hash_list_iter_has_next(iter)) {
		struct parq_ul_queued *puq = hash_list_iter_next(iter);

		parq_ul_queued_check(puq);
		g_assert_log(puq->relative_position > old_relative,
			"relative=%u, old=%u", puq->relative_position, old_relative);
		old_relative = puq->relative_position;

		if (
			puq->relative_position >= item->relative_position ||
			puq->relative_position > GNET_PROPERTY(max_uploads)
		)
			break;

		g_debug("[PARQ UL] Q#%d pos=%u, rel=%u, slot<has=%s had=%s> updated=%s"
			" active=%s, quick=%s, alive=%s, flags=0x%x, ID=%s, expire=%s ",
			q->num, puq->position, puq->relative_position,
			puq->has_slot ? "y" : "n", puq->had_slot ? "y" : "n",
			compact_time(delta_time(tm_time(), puq->updated)),
			puq->active_queued ? "y" : "n", puq->quick ? "y" : "n",
			puq->is_alive ? "y" : "n", puq->flags, guid_hex_str(&puq->id),
			timestamp_utc_to_string(puq->expire));
	}

	hash_list_iter_release(&iter);
}
