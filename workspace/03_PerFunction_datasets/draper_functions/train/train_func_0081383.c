reset_psn(struct hfi1_qp *qp, u32 psn)
{
	u32 n = qp->s_acked;
	struct hfi1_swqe *wqe = get_swqe_ptr(qp, n);
	u32 opcode;

	qp->s_cur = n;


	if (cmp_psn(psn, wqe->psn) <= 0) {
		qp->s_state = OP(SEND_LAST);
		goto done;
	}


	opcode = wqe->wr.opcode;
	for (;;) {
		int diff;

		if (++n == qp->s_size)
			n = 0;
		if (n == qp->s_tail)
			break;
		wqe = get_swqe_ptr(qp, n);
		diff = cmp_psn(psn, wqe->psn);
		if (diff < 0)
			break;
		qp->s_cur = n;


		if (diff == 0) {
			qp->s_state = OP(SEND_LAST);
			goto done;
		}
		opcode = wqe->wr.opcode;
	}


	switch (opcode) {
	case IB_WR_SEND:
	case IB_WR_SEND_WITH_IMM:
		qp->s_state = OP(RDMA_READ_RESPONSE_FIRST);
		break;

	case IB_WR_RDMA_WRITE:
	case IB_WR_RDMA_WRITE_WITH_IMM:
		qp->s_state = OP(RDMA_READ_RESPONSE_LAST);
		break;

	case IB_WR_RDMA_READ:
		qp->s_state = OP(RDMA_READ_RESPONSE_MIDDLE);
		break;

	default:


		qp->s_state = OP(SEND_LAST);
	}
done:
	qp->s_psn = psn;


	if ((cmp_psn(qp->s_psn, qp->s_sending_hpsn) <= 0) &&
	    (cmp_psn(qp->s_sending_psn, qp->s_sending_hpsn) <= 0))
		qp->s_flags |= HFI1_S_WAIT_PSN;
	qp->s_flags &= ~HFI1_S_AHG_VALID;
}
