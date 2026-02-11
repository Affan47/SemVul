qlcnic_83xx_del_tx_ctx(struct qlcnic_adapter *adapter,
			    struct qlcnic_host_tx_ring *tx_ring)
{
	struct qlcnic_cmd_args cmd;
	u32 temp = 0;

	if (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_DESTROY_TX_CTX))
		return;

	if (qlcnic_sriov_pf_check(adapter) || qlcnic_sriov_vf_check(adapter))
		cmd.req.arg[0] |= (0x3 << 29);

	if (qlcnic_sriov_pf_check(adapter))
		qlcnic_pf_set_interface_id_del_tx_ctx(adapter, &temp);

	cmd.req.arg[1] = tx_ring->ctx_id | temp;
	if (qlcnic_issue_cmd(adapter, &cmd))
		dev_err(&adapter->pdev->dev,
			"Failed to destroy tx ctx in firmware\n");
	qlcnic_free_mbx_args(&cmd);
}
