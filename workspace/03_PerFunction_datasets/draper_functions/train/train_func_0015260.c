bnx2x_sriov_info(struct bnx2x *bp, struct bnx2x_sriov *iov)
{
	u32 val;


	if (bnx2x_sriov_pci_cfg_info(bp, iov))
		return -ENODEV;


	iov->nres = 0;


	val = REG_RD(bp, PCICFG_OFFSET + GRC_CONFIG_REG_PF_INIT_VF);
	iov->first_vf_in_pf = ((val & GRC_CR_PF_INIT_VF_PF_FIRST_VF_NUM_MASK)
			       * 8) - (BNX2X_MAX_NUM_OF_VFS * BP_PATH(bp));

	DP(BNX2X_MSG_IOV,
	   "IOV info[%d]: first vf %d, nres %d, cap 0x%x, ctrl 0x%x, total %d, initial %d, num vfs %d, offset %d, stride %d, page size 0x%x\n",
	   BP_FUNC(bp),
	   iov->first_vf_in_pf, iov->nres, iov->cap, iov->ctrl, iov->total,
	   iov->initial, iov->nr_virtfn, iov->offset, iov->stride, iov->pgsz);

	return 0;
}
