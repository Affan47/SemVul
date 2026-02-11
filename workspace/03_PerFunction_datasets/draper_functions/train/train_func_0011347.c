qlcnic_sriov_pf_cfg_eswitch(struct qlcnic_adapter *adapter,
				       u8 func, u8 enable)
{
	struct qlcnic_cmd_args cmd;
	int err = -EIO;

	if (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_TOGGLE_ESWITCH))
		return -ENOMEM;

	cmd.req.arg[0] |= (3 << 29);
	cmd.req.arg[1] = ((func & 0xf) << 2) | BIT_6 | BIT_1;
	if (enable)
		cmd.req.arg[1] |= BIT_0;

	err = qlcnic_issue_cmd(adapter, &cmd);

	if (err != QLCNIC_RCODE_SUCCESS) {
		dev_err(&adapter->pdev->dev,
			"Failed to enable sriov eswitch%d\n", err);
		err = -EIO;
	}

	qlcnic_free_mbx_args(&cmd);
	return err;
}
