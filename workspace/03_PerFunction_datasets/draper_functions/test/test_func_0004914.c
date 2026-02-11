blkif_queue_rq(struct blk_mq_hw_ctx *hctx,
			   const struct blk_mq_queue_data *qd)
{
	struct blkfront_info *info = qd->rq->rq_disk->private_data;

	blk_mq_start_request(qd->rq);
	spin_lock_irq(&info->io_lock);
	if (RING_FULL(&info->ring))
		goto out_busy;

	if (blkif_request_flush_invalid(qd->rq, info))
		goto out_err;

	if (blkif_queue_request(qd->rq))
		goto out_busy;

	flush_requests(info);
	spin_unlock_irq(&info->io_lock);
	return BLK_MQ_RQ_QUEUE_OK;

out_err:
	spin_unlock_irq(&info->io_lock);
	return BLK_MQ_RQ_QUEUE_ERROR;

out_busy:
	spin_unlock_irq(&info->io_lock);
	blk_mq_stop_hw_queue(hctx);
	return BLK_MQ_RQ_QUEUE_BUSY;
}
