blk_execute_rq_nowait(struct request_queue *q, struct gendisk *bd_disk,
			   struct request *rq, int at_head,
			   rq_end_io_fn *done)
{
	int where = at_head ? ELEVATOR_INSERT_FRONT : ELEVATOR_INSERT_BACK;

	WARN_ON(irqs_disabled());
	WARN_ON(rq->cmd_type == REQ_TYPE_FS);

	rq->rq_disk = bd_disk;
	rq->end_io = done;


	if (q->mq_ops) {
		blk_mq_insert_request(rq, at_head, true, false);
		return;
	}

	spin_lock_irq(q->queue_lock);

	if (unlikely(blk_queue_dying(q))) {
		rq->cmd_flags |= REQ_QUIET;
		rq->errors = -ENXIO;
		__blk_end_request_all(rq, rq->errors);
		spin_unlock_irq(q->queue_lock);
		return;
	}

	__elv_add_request(q, rq, where);
	__blk_run_queue(q);
	spin_unlock_irq(q->queue_lock);
}
