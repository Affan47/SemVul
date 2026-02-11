cxio_hal_cq_op(struct cxio_rdev *rdev_p, struct t3_cq *cq,
		   enum t3_cq_opcode op, u32 credit)
{
	int ret;
	struct t3_cqe *cqe;
	u32 rptr;

	struct rdma_cq_op setup;
	setup.id = cq->cqid;
	setup.credits = (op == CQ_CREDIT_UPDATE) ? credit : 0;
	setup.op = op;
	ret = rdev_p->t3cdev_p->ctl(rdev_p->t3cdev_p, RDMA_CQ_OP, &setup);

	if ((ret < 0) || (op == CQ_CREDIT_UPDATE))
		return ret;


	if (Q_PTR2IDX((cq->rptr), cq->size_log2) != ret) {
		int i=0;

		rptr = cq->rptr;


		while (Q_PTR2IDX((rptr+1), cq->size_log2) != ret)
			rptr++;


		cqe = cq->queue + Q_PTR2IDX(rptr, cq->size_log2);
		while (!CQ_VLD_ENTRY(rptr, cq->size_log2, cqe)) {
			udelay(1);
			if (i++ > 1000000) {
				printk(KERN_ERR "%s: stalled rnic\n",
				       rdev_p->dev_name);
				return -EIO;
			}
		}

		return 1;
	}

	return 0;
}
