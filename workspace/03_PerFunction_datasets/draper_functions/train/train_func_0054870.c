qp_idle(struct hfi1_qp *qp)
{
	return
		qp->s_last == qp->s_acked &&
		qp->s_acked == qp->s_cur &&
		qp->s_cur == qp->s_tail &&
		qp->s_tail == qp->s_head;
}
