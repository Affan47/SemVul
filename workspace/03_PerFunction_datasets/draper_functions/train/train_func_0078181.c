blk_flush_plug_list(struct blk_plug *plug, bool from_schedule)
{
	struct request_queue *q;
	unsigned long flags;
	struct request *rq;
	LIST_HEAD(list);
	unsigned int depth;

	flush_plug_callbacks(plug, from_schedule);

	if (!list_empty(&plug->mq_list))
		blk_mq_flush_plug_list(plug, from_schedule);

	if (list_empty(&plug->list))
		return;

	list_splice_init(&plug->list, &list);

	list_sort(NULL, &list, plug_rq_cmp);

	q = NULL;
	depth = 0;


	local_irq_save(flags);
	while (!list_empty(&list)) {
		rq = list_entry_rq(list.next);
		list_del_init(&rq->queuelist);
		BUG_ON(!rq->q);
		if (rq->q != q) {


			if (q)
				queue_unplugged(q, depth, from_schedule);
			q = rq->q;
			depth = 0;
			spin_lock(q->queue_lock);
		}


		if (unlikely(blk_queue_dying(q))) {
			__blk_end_request_all(rq, -ENODEV);
			continue;
		}


		if (rq->cmd_flags & (REQ_FLUSH | REQ_FUA))
			__elv_add_request(q, rq, ELEVATOR_INSERT_FLUSH);
		else
			__elv_add_request(q, rq, ELEVATOR_INSERT_SORT_MERGE);

		depth++;
	}


	if (q)
		queue_unplugged(q, depth, from_schedule);

	local_irq_restore(flags);
}
