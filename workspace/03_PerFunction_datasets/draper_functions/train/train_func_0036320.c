elv_attempt_insert_merge(struct request_queue *q,
				     struct request *rq)
{
	struct request *__rq;
	bool ret;

	if (blk_queue_nomerges(q))
		return false;


	if (q->last_merge && blk_attempt_req_merge(q, q->last_merge, rq))
		return true;

	if (blk_queue_noxmerges(q))
		return false;

	ret = false;


	while (1) {
		__rq = elv_rqhash_find(q, blk_rq_pos(rq));
		if (!__rq || !blk_attempt_req_merge(q, __rq, rq))
			break;


		ret = true;
		rq = __rq;
	}

	return ret;
}
