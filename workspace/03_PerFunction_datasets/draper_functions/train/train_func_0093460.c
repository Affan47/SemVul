iwch_query_device(struct ib_device *ibdev, struct ib_device_attr *props,
			     struct ib_udata *uhw)
{

	struct iwch_dev *dev;

	PDBG("%s ibdev %p\n", __func__, ibdev);

	if (uhw->inlen || uhw->outlen)
		return -EINVAL;

	dev = to_iwch_dev(ibdev);
	memset(props, 0, sizeof *props);
	memcpy(&props->sys_image_guid, dev->rdev.t3cdev_p->lldev->dev_addr, 6);
	props->hw_ver = dev->rdev.t3cdev_p->type;
	props->fw_ver = fw_vers_string_to_u64(dev);
	props->device_cap_flags = dev->device_cap_flags;
	props->page_size_cap = dev->attr.mem_pgsizes_bitmask;
	props->vendor_id = (u32)dev->rdev.rnic_info.pdev->vendor;
	props->vendor_part_id = (u32)dev->rdev.rnic_info.pdev->device;
	props->max_mr_size = dev->attr.max_mr_size;
	props->max_qp = dev->attr.max_qps;
	props->max_qp_wr = dev->attr.max_wrs;
	props->max_sge = dev->attr.max_sge_per_wr;
	props->max_sge_rd = 1;
	props->max_qp_rd_atom = dev->attr.max_rdma_reads_per_qp;
	props->max_qp_init_rd_atom = dev->attr.max_rdma_reads_per_qp;
	props->max_cq = dev->attr.max_cqs;
	props->max_cqe = dev->attr.max_cqes_per_cq;
	props->max_mr = dev->attr.max_mem_regs;
	props->max_pd = dev->attr.max_pds;
	props->local_ca_ack_delay = 0;
	props->max_fast_reg_page_list_len = T3_MAX_FASTREG_DEPTH;

	return 0;
}
