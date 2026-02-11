get_rdac_req(struct scsi_device *sdev,
			void *buffer, unsigned buflen, int rw)
{
	struct request *rq;
	struct request_queue *q = sdev->request_queue;

	rq = blk_get_request(q, rw, GFP_NOIO);

	if (IS_ERR(rq)) {
		sdev_printk(KERN_INFO, sdev,
				"get_rdac_req: blk_get_request failed.\n");
		return NULL;
	}
	blk_rq_set_block_pc(rq);

	if (buflen && blk_rq_map_kern(q, rq, buffer, buflen, GFP_NOIO)) {
		blk_put_request(rq);
		sdev_printk(KERN_INFO, sdev,
				"get_rdac_req: blk_rq_map_kern failed.\n");
		return NULL;
	}

	rq->cmd_flags |= REQ_FAILFAST_DEV | REQ_FAILFAST_TRANSPORT |
			 REQ_FAILFAST_DRIVER;
	rq->retries = RDAC_RETRIES;
	rq->timeout = RDAC_TIMEOUT;

	return rq;
}
