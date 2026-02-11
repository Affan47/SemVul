ocrdma_update_free_srq_cqe(struct ib_wc *ibwc,
				       struct ocrdma_cqe *cqe,
				       struct ocrdma_qp *qp)
{
	unsigned long flags;
	struct ocrdma_srq *srq;
	u32 wqe_idx;

	srq = get_ocrdma_srq(qp->ibqp.srq);
	wqe_idx = (le32_to_cpu(cqe->rq.buftag_qpn) >>
		OCRDMA_CQE_BUFTAG_SHIFT) & srq->rq.max_wqe_idx;
	if (wqe_idx < 1)
		BUG();

	ibwc->wr_id = srq->rqe_wr_id_tbl[wqe_idx];
	spin_lock_irqsave(&srq->q_lock, flags);
	ocrdma_srq_toggle_bit(srq, wqe_idx - 1);
	spin_unlock_irqrestore(&srq->q_lock, flags);
	ocrdma_hwq_inc_tail(&srq->rq);
}
