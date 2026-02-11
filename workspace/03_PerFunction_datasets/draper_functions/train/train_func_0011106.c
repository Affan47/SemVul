nvme_init_iod(struct request *rq, struct nvme_dev *dev)
{
	struct nvme_iod *iod = blk_mq_rq_to_pdu(rq);
	int nseg = rq->nr_phys_segments;
	unsigned size;

	if (rq->cmd_flags & REQ_DISCARD)
		size = sizeof(struct nvme_dsm_range);
	else
		size = blk_rq_bytes(rq);

	if (nseg > NVME_INT_PAGES || size > NVME_INT_BYTES(dev)) {
		iod->sg = kmalloc(nvme_iod_alloc_size(dev, size, nseg), GFP_ATOMIC);
		if (!iod->sg)
			return BLK_MQ_RQ_QUEUE_BUSY;
	} else {
		iod->sg = iod->inline_sg;
	}

	iod->aborted = 0;
	iod->npages = -1;
	iod->nents = 0;
	iod->length = size;
	return 0;
}
