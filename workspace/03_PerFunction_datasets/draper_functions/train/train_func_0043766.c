qlcnic_83xx_config_intrpt(struct qlcnic_adapter *adapter, bool op_type)
{
	int i, index, err;
	u8 max_ints;
	u32 val, temp, type;
	struct qlcnic_cmd_args cmd;

	max_ints = adapter->ahw->num_msix - 1;
	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CONFIG_INTRPT);
	if (err)
		return err;

	cmd.req.arg[1] = max_ints;

	if (qlcnic_sriov_vf_check(adapter))
		cmd.req.arg[1] |= (adapter->ahw->pci_func << 8) | BIT_16;

	for (i = 0, index = 2; i < max_ints; i++) {
		type = op_type ? QLCNIC_INTRPT_ADD : QLCNIC_INTRPT_DEL;
		val = type | (adapter->ahw->intr_tbl[i].type << 4);
		if (adapter->ahw->intr_tbl[i].type == QLCNIC_INTRPT_MSIX)
			val |= (adapter->ahw->intr_tbl[i].id << 16);
		cmd.req.arg[index++] = val;
	}
	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err) {
		dev_err(&adapter->pdev->dev,
			"Failed to configure interrupts 0x%x\n", err);
		goto out;
	}

	max_ints = cmd.rsp.arg[1];
	for (i = 0, index = 2; i < max_ints; i++, index += 2) {
		val = cmd.rsp.arg[index];
		if (LSB(val)) {
			dev_info(&adapter->pdev->dev,
				 "Can't configure interrupt %d\n",
				 adapter->ahw->intr_tbl[i].id);
			continue;
		}
		if (op_type) {
			adapter->ahw->intr_tbl[i].id = MSW(val);
			adapter->ahw->intr_tbl[i].enabled = 1;
			temp = cmd.rsp.arg[index + 1];
			adapter->ahw->intr_tbl[i].src = temp;
		} else {
			adapter->ahw->intr_tbl[i].id = i;
			adapter->ahw->intr_tbl[i].enabled = 0;
			adapter->ahw->intr_tbl[i].src = 0;
		}
	}
out:
	qlcnic_free_mbx_args(&cmd);
	return err;
}
