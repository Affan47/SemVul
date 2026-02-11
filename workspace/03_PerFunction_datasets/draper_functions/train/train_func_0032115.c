ocrdma_create_mq(struct ocrdma_dev *dev)
{
	int status;


	status = ocrdma_alloc_q(dev, &dev->mq.cq, OCRDMA_MQ_CQ_LEN,
				sizeof(struct ocrdma_mcqe));
	if (status)
		goto alloc_err;

	dev->eq_tbl[0].cq_cnt++;
	status = ocrdma_mbx_mq_cq_create(dev, &dev->mq.cq, &dev->eq_tbl[0].q);
	if (status)
		goto mbx_cq_free;

	memset(&dev->mqe_ctx, 0, sizeof(dev->mqe_ctx));
	init_waitqueue_head(&dev->mqe_ctx.cmd_wait);
	mutex_init(&dev->mqe_ctx.lock);


	status = ocrdma_alloc_q(dev, &dev->mq.sq, OCRDMA_MQ_LEN,
				sizeof(struct ocrdma_mqe));
	if (status)
		goto mbx_cq_destroy;
	status = ocrdma_mbx_create_mq(dev, &dev->mq.sq, &dev->mq.cq);
	if (status)
		goto mbx_q_free;
	ocrdma_ring_cq_db(dev, dev->mq.cq.id, true, false, 0);
	return 0;

mbx_q_free:
	ocrdma_free_q(dev, &dev->mq.sq);
mbx_cq_destroy:
	ocrdma_mbx_delete_q(dev, &dev->mq.cq, QTYPE_CQ);
mbx_cq_free:
	ocrdma_free_q(dev, &dev->mq.cq);
alloc_err:
	return status;
}
