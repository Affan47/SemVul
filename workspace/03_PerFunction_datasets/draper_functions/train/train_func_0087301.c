msb_io_work(struct work_struct *work)
{
	struct msb_data *msb = container_of(work, struct msb_data, io_work);
	int page, error, len;
	sector_t lba;
	unsigned long flags;
	struct scatterlist *sg = msb->prealloc_sg;

	dbg_verbose("IO: work started");

	while (1) {
		spin_lock_irqsave(&msb->q_lock, flags);

		if (msb->need_flush_cache) {
			msb->need_flush_cache = false;
			spin_unlock_irqrestore(&msb->q_lock, flags);
			msb_cache_flush(msb);
			continue;
		}

		if (!msb->req) {
			msb->req = blk_fetch_request(msb->queue);
			if (!msb->req) {
				dbg_verbose("IO: no more requests exiting");
				spin_unlock_irqrestore(&msb->q_lock, flags);
				return;
			}
		}

		spin_unlock_irqrestore(&msb->q_lock, flags);


		if (!msb->req)
			return;


		dbg_verbose("IO: processing new request");
		blk_rq_map_sg(msb->queue, msb->req, sg);

		lba = blk_rq_pos(msb->req);

		sector_div(lba, msb->page_size / 512);
		page = do_div(lba, msb->pages_in_block);

		if (rq_data_dir(msb->req) == READ)
			error = msb_do_read_request(msb, lba, page, sg,
				blk_rq_bytes(msb->req), &len);
		else
			error = msb_do_write_request(msb, lba, page, sg,
				blk_rq_bytes(msb->req), &len);

		spin_lock_irqsave(&msb->q_lock, flags);

		if (len)
			if (!__blk_end_request(msb->req, 0, len))
				msb->req = NULL;

		if (error && msb->req) {
			dbg_verbose("IO: ending one sector of the request with error");
			if (!__blk_end_request(msb->req, error, msb->page_size))
				msb->req = NULL;
		}

		if (msb->req)
			dbg_verbose("IO: request still pending");

		spin_unlock_irqrestore(&msb->q_lock, flags);
	}
}
