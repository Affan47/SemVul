dump_err_cqe(struct c4iw_dev *dev, struct t4_cqe *err_cqe)
{
	__be64 *p = (void *)err_cqe;

	dev_err(&dev->rdev.lldi.pdev->dev,
		"AE qpid %d opcode %d status 0x%x "
		"type %d len 0x%x wrid.hi 0x%x wrid.lo 0x%x\n",
		CQE_QPID(err_cqe), CQE_OPCODE(err_cqe),
		CQE_STATUS(err_cqe), CQE_TYPE(err_cqe), ntohl(err_cqe->len),
		CQE_WRID_HI(err_cqe), CQE_WRID_LOW(err_cqe));

	PDBG("%016llx %016llx %016llx %016llx\n",
	     be64_to_cpu(p[0]), be64_to_cpu(p[1]), be64_to_cpu(p[2]),
	     be64_to_cpu(p[3]));


	if (RQ_TYPE(err_cqe) && (CQE_OPCODE(err_cqe) == FW_RI_RDMA_WRITE ||
				 CQE_OPCODE(err_cqe) == FW_RI_READ_RESP))
		print_tpte(dev, CQE_WRID_STAG(err_cqe));
}
