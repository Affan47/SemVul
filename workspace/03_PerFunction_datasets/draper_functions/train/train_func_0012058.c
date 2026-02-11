ocrdma_destroy_qp(struct ib_qp *ibqp)
{
	struct ocrdma_pd *pd;
	struct ocrdma_qp *qp;
	struct ocrdma_dev *dev;
	struct ib_qp_attr attrs;
	int attr_mask;
	unsigned long flags;

	qp = get_ocrdma_qp(ibqp);
	dev = get_ocrdma_dev(ibqp->device);

	pd = qp->pd;


	if (qp->state != OCRDMA_QPS_RST) {
		attrs.qp_state = IB_QPS_ERR;
		attr_mask = IB_QP_STATE;
		_ocrdma_modify_qp(ibqp, &attrs, attr_mask);
	}


	mutex_lock(&dev->dev_lock);
	(void) ocrdma_mbx_destroy_qp(dev, qp);


	spin_lock_irqsave(&qp->sq_cq->cq_lock, flags);
	if (qp->rq_cq && (qp->rq_cq != qp->sq_cq))
		spin_lock(&qp->rq_cq->cq_lock);

	ocrdma_del_qpn_map(dev, qp);

	if (qp->rq_cq && (qp->rq_cq != qp->sq_cq))
		spin_unlock(&qp->rq_cq->cq_lock);
	spin_unlock_irqrestore(&qp->sq_cq->cq_lock, flags);

	if (!pd->uctx) {
		ocrdma_discard_cqes(qp, qp->sq_cq);
		ocrdma_discard_cqes(qp, qp->rq_cq);
	}
	mutex_unlock(&dev->dev_lock);

	if (pd->uctx) {
		ocrdma_del_mmap(pd->uctx, (u64) qp->sq.pa,
				PAGE_ALIGN(qp->sq.len));
		if (!qp->srq)
			ocrdma_del_mmap(pd->uctx, (u64) qp->rq.pa,
					PAGE_ALIGN(qp->rq.len));
	}

	ocrdma_del_flush_qp(qp);

	kfree(qp->wqe_wr_id_tbl);
	kfree(qp->rqe_wr_id_tbl);
	kfree(qp);
	return 0;
}
