ocrdma_build_send(struct ocrdma_qp *qp, struct ocrdma_hdr_wqe *hdr,
			     struct ib_send_wr *wr)
{
	int status;
	struct ocrdma_sge *sge;
	u32 wqe_size = sizeof(*hdr);

	if (qp->qp_type == IB_QPT_UD || qp->qp_type == IB_QPT_GSI) {
		ocrdma_build_ud_hdr(qp, hdr, wr);
		sge = (struct ocrdma_sge *)(hdr + 2);
		wqe_size += sizeof(struct ocrdma_ewqe_ud_hdr);
	} else {
		sge = (struct ocrdma_sge *)(hdr + 1);
	}

	status = ocrdma_build_inline_sges(qp, hdr, sge, wr, wqe_size);
	return status;
}
