pkt_generic_packet(struct pktcdvd_device *pd, struct packet_command *cgc)
{
	struct request_queue *q = bdev_get_queue(pd->bdev);
	struct request *rq;
	int ret = 0;

	rq = blk_get_request(q, (cgc->data_direction == CGC_DATA_WRITE) ?
			     WRITE : READ, __GFP_RECLAIM);
	if (IS_ERR(rq))
		return PTR_ERR(rq);
	blk_rq_set_block_pc(rq);

	if (cgc->buflen) {
		ret = blk_rq_map_kern(q, rq, cgc->buffer, cgc->buflen,
				      __GFP_RECLAIM);
		if (ret)
			goto out;
	}

	rq->cmd_len = COMMAND_SIZE(cgc->cmd[0]);
	memcpy(rq->cmd, cgc->cmd, CDROM_PACKET_SIZE);

	rq->timeout = 60*HZ;
	if (cgc->quiet)
		rq->cmd_flags |= REQ_QUIET;

	blk_execute_rq(rq->q, pd->bdev->bd_disk, rq, 0);
	if (rq->errors)
		ret = -EIO;
out:
	blk_put_request(rq);
	return ret;
}
