build_zero_stag_recv(struct iwch_qp *qhp, union t3_wr *wqe,
				struct ib_recv_wr *wr)
{
	int i;
	u32 pbl_addr;
	u32 pbl_offset;


	pbl_addr = cxio_hal_pblpool_alloc(&qhp->rhp->rdev, T3_STAG0_PBL_SIZE);
	if (!pbl_addr)
		return -ENOMEM;


	pbl_offset = (pbl_addr - qhp->rhp->rdev.rnic_info.pbl_base) >> 3;

	wqe->recv.num_sgle = cpu_to_be32(wr->num_sge);

	for (i = 0; i < wr->num_sge; i++) {


		if (wr->sg_list[i].length > T3_STAG0_MAX_PBE_LEN)
			return -EINVAL;
		wqe->recv.pagesz[i] = T3_STAG0_PAGE_SHIFT;


		if (wr->sg_list[i].lkey != 0)
			return -EINVAL;
		wqe->recv.sgl[i].stag = 0;
		wqe->recv.sgl[i].len = cpu_to_be32(wr->sg_list[i].length);
		wqe->recv.sgl[i].to = cpu_to_be64(wr->sg_list[i].addr);
		wqe->recv.pbl_addr[i] = cpu_to_be32(pbl_offset);
		pbl_offset += 2;
	}
	for (; i < T3_MAX_SGE; i++) {
		wqe->recv.pagesz[i] = 0;
		wqe->recv.sgl[i].stag = 0;
		wqe->recv.sgl[i].len = 0;
		wqe->recv.sgl[i].to = 0;
		wqe->recv.pbl_addr[i] = 0;
	}
	qhp->wq.rq[Q_PTR2IDX(qhp->wq.rq_wptr,
			     qhp->wq.rq_size_log2)].wr_id = wr->wr_id;
	qhp->wq.rq[Q_PTR2IDX(qhp->wq.rq_wptr,
			     qhp->wq.rq_size_log2)].pbl_addr = pbl_addr;
	return 0;
}
