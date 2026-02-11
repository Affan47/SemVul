cnic_bnx2x_fcoe_init1(struct cnic_dev *dev, struct kwqe *wqes[],
				 u32 num, int *work)
{
	int ret;
	struct cnic_local *cp = dev->cnic_priv;
	struct bnx2x *bp = netdev_priv(dev->netdev);
	u32 cid;
	struct fcoe_init_ramrod_params *fcoe_init;
	struct fcoe_kwqe_init1 *req1;
	struct fcoe_kwqe_init2 *req2;
	struct fcoe_kwqe_init3 *req3;
	union l5cm_specific_data l5_data;

	if (num < 3) {
		*work = num;
		return -EINVAL;
	}
	req1 = (struct fcoe_kwqe_init1 *) wqes[0];
	req2 = (struct fcoe_kwqe_init2 *) wqes[1];
	req3 = (struct fcoe_kwqe_init3 *) wqes[2];
	if (req2->hdr.op_code != FCOE_KWQE_OPCODE_INIT2) {
		*work = 1;
		return -EINVAL;
	}
	if (req3->hdr.op_code != FCOE_KWQE_OPCODE_INIT3) {
		*work = 2;
		return -EINVAL;
	}

	if (sizeof(*fcoe_init) > CNIC_KWQ16_DATA_SIZE) {
		netdev_err(dev->netdev, "fcoe_init size too big\n");
		return -ENOMEM;
	}
	fcoe_init = cnic_get_kwqe_16_data(cp, BNX2X_FCOE_L5_CID_BASE, &l5_data);
	if (!fcoe_init)
		return -ENOMEM;

	memset(fcoe_init, 0, sizeof(*fcoe_init));
	memcpy(&fcoe_init->init_kwqe1, req1, sizeof(*req1));
	memcpy(&fcoe_init->init_kwqe2, req2, sizeof(*req2));
	memcpy(&fcoe_init->init_kwqe3, req3, sizeof(*req3));
	fcoe_init->eq_pbl_base.lo = cp->kcq2.dma.pgtbl_map & 0xffffffff;
	fcoe_init->eq_pbl_base.hi = (u64) cp->kcq2.dma.pgtbl_map >> 32;
	fcoe_init->eq_pbl_size = cp->kcq2.dma.num_pages;

	fcoe_init->sb_num = cp->status_blk_num;
	fcoe_init->eq_prod = MAX_KCQ_IDX;
	fcoe_init->sb_id = HC_INDEX_FCOE_EQ_CONS;
	cp->kcq2.sw_prod_idx = 0;

	cid = BNX2X_HW_CID(bp, cp->fcoe_init_cid);
	ret = cnic_submit_kwqe_16(dev, FCOE_RAMROD_CMD_ID_INIT_FUNC, cid,
				  FCOE_CONNECTION_TYPE, &l5_data);
	*work = 3;
	return ret;
}
