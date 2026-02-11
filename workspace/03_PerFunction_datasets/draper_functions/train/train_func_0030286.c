qlcnic_83xx_create_tx_ctx(struct qlcnic_adapter *adapter,
			      struct qlcnic_host_tx_ring *tx, int ring)
{
	int err;
	u16 msix_id;
	u32 *buf, intr_mask, temp = 0;
	struct qlcnic_cmd_args cmd;
	struct qlcnic_tx_mbx mbx;
	struct qlcnic_tx_mbx_out *mbx_out;
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	u32 msix_vector;


	tx->producer = 0;
	tx->sw_consumer = 0;
	*(tx->hw_consumer) = 0;

	memset(&mbx, 0, sizeof(struct qlcnic_tx_mbx));


	mbx.phys_addr_low = LSD(tx->phys_addr);
	mbx.phys_addr_high = MSD(tx->phys_addr);
	mbx.cnsmr_index_low = LSD(tx->hw_cons_phys_addr);
	mbx.cnsmr_index_high = MSD(tx->hw_cons_phys_addr);
	mbx.size = tx->num_desc;
	if (adapter->flags & QLCNIC_MSIX_ENABLED) {
		if (!(adapter->flags & QLCNIC_TX_INTR_SHARED))
			msix_vector = adapter->drv_sds_rings + ring;
		else
			msix_vector = adapter->drv_sds_rings - 1;
		msix_id = ahw->intr_tbl[msix_vector].id;
	} else {
		msix_id = QLCRDX(ahw, QLCNIC_DEF_INT_ID);
	}

	if (adapter->ahw->diag_test != QLCNIC_LOOPBACK_TEST)
		mbx.intr_id = msix_id;
	else
		mbx.intr_id = 0xffff;
	mbx.src = 0;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CREATE_TX_CTX);
	if (err)
		return err;

	if (qlcnic_sriov_pf_check(adapter) || qlcnic_sriov_vf_check(adapter))
		cmd.req.arg[0] |= (0x3 << 29);

	if (qlcnic_sriov_pf_check(adapter))
		qlcnic_pf_set_interface_id_create_tx_ctx(adapter, &temp);

	cmd.req.arg[1] = QLCNIC_CAP0_LEGACY_CONTEXT;
	cmd.req.arg[5] = QLCNIC_SINGLE_RING | temp;

	buf = &cmd.req.arg[6];
	memcpy(buf, &mbx, sizeof(struct qlcnic_tx_mbx));

	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err) {
		netdev_err(adapter->netdev,
			   "Failed to create Tx ctx in firmware 0x%x\n", err);
		goto out;
	}
	mbx_out = (struct qlcnic_tx_mbx_out *)&cmd.rsp.arg[2];
	tx->crb_cmd_producer = ahw->pci_base0 + mbx_out->host_prod;
	tx->ctx_id = mbx_out->ctx_id;
	if ((adapter->flags & QLCNIC_MSIX_ENABLED) &&
	    !(adapter->flags & QLCNIC_TX_INTR_SHARED)) {
		intr_mask = ahw->intr_tbl[adapter->drv_sds_rings + ring].src;
		tx->crb_intr_mask = ahw->pci_base0 + intr_mask;
	}
	netdev_info(adapter->netdev,
		    "Tx Context[0x%x] Created, state:0x%x\n",
		    tx->ctx_id, mbx_out->state);
out:
	qlcnic_free_mbx_args(&cmd);
	return err;
}
