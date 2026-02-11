dm_dispatch_clone_request(struct request *clone, struct request *rq)
{
	int r;

	if (blk_queue_io_stat(clone->q))
		clone->cmd_flags |= REQ_IO_STAT;

	clone->start_time = jiffies;
	r = blk_insert_cloned_request(clone->q, clone);
	if (r)

		dm_complete_request(rq, r);
}
