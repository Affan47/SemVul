mthca_free_err_wqe(struct mthca_dev *dev, struct mthca_qp *qp, int is_send,
			int index, int *dbd, __be32 *new_wqe)
{
	struct mthca_next_seg *next;


	if (qp->ibqp.srq && !is_send) {
		*new_wqe = 0;
		return;
	}

	if (is_send)
		next = get_send_wqe(qp, index);
	else
		next = get_recv_wqe(qp, index);

	*dbd = !!(next->ee_nds & cpu_to_be32(MTHCA_NEXT_DBD));
	if (next->ee_nds & cpu_to_be32(0x3f))
		*new_wqe = (next->nda_op & cpu_to_be32(~0x3f)) |
			(next->ee_nds & cpu_to_be32(0x3f));
	else
		*new_wqe = 0;
}
