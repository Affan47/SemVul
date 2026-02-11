dm_mq_queue_rq(struct blk_mq_hw_ctx *hctx,
			  const struct blk_mq_queue_data *bd)
{
	struct request *rq = bd->rq;
	struct dm_rq_target_io *tio = blk_mq_rq_to_pdu(rq);
	struct mapped_device *md = tio->md;
	int srcu_idx;
	struct dm_table *map = dm_get_live_table(md, &srcu_idx);
	struct dm_target *ti;
	sector_t pos;


	pos = 0;
	if (!(rq->cmd_flags & REQ_FLUSH))
		pos = blk_rq_pos(rq);

	ti = dm_table_find_target(map, pos);
	if (!dm_target_is_valid(ti)) {
		dm_put_live_table(md, srcu_idx);
		DMERR_LIMIT("request attempted access beyond the end of device");


		dm_start_request(md, rq);
		return BLK_MQ_RQ_QUEUE_ERROR;
	}
	dm_put_live_table(md, srcu_idx);

	if (ti->type->busy && ti->type->busy(ti))
		return BLK_MQ_RQ_QUEUE_BUSY;

	dm_start_request(md, rq);


	init_tio(tio, rq, md);


	tio->ti = ti;


	if (dm_table_get_type(map) == DM_TYPE_REQUEST_BASED) {

		tio->clone = (void *)blk_mq_rq_to_pdu(rq) + sizeof(struct dm_rq_target_io);
		(void) clone_rq(rq, md, tio, GFP_ATOMIC);
		queue_kthread_work(&md->kworker, &tio->work);
	} else {

		if (map_request(tio, rq, md) == DM_MAPIO_REQUEUE) {

			rq_end_stats(md, rq);
			rq_completed(md, rq_data_dir(rq), false);
			return BLK_MQ_RQ_QUEUE_BUSY;
		}
	}

	return BLK_MQ_RQ_QUEUE_OK;
}
