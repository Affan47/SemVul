ocrdma_set_create_qp_ird_cmd(struct ocrdma_create_qp_req *cmd,
					struct ocrdma_qp *qp)
{
	struct ocrdma_pd *pd = qp->pd;
	struct ocrdma_dev *dev = get_ocrdma_dev(pd->ibpd.device);
	struct pci_dev *pdev = dev->nic_info.pdev;
	dma_addr_t pa = 0;
	int ird_page_size = dev->attr.ird_page_size;
	int ird_q_len = dev->attr.num_ird_pages * ird_page_size;
	struct ocrdma_hdr_wqe *rqe;
	int i  = 0;

	if (dev->attr.ird == 0)
		return 0;

	qp->ird_q_va = dma_alloc_coherent(&pdev->dev, ird_q_len,
					&pa, GFP_KERNEL);
	if (!qp->ird_q_va)
		return -ENOMEM;
	memset(qp->ird_q_va, 0, ird_q_len);
	ocrdma_build_q_pages(&cmd->ird_addr[0], dev->attr.num_ird_pages,
			     pa, ird_page_size);
	for (; i < ird_q_len / dev->attr.rqe_size; i++) {
		rqe = (struct ocrdma_hdr_wqe *)(qp->ird_q_va +
			(i * dev->attr.rqe_size));
		rqe->cw = 0;
		rqe->cw |= 2;
		rqe->cw |= (OCRDMA_TYPE_LKEY << OCRDMA_WQE_TYPE_SHIFT);
		rqe->cw |= (8 << OCRDMA_WQE_SIZE_SHIFT);
		rqe->cw |= (8 << OCRDMA_WQE_NXT_WQE_SIZE_SHIFT);
	}
	return 0;
}
