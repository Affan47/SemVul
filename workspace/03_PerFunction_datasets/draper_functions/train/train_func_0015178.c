qlcnic_83xx_interrupt_test(struct net_device *netdev)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlcnic_cmd_args cmd;
	u8 val, drv_sds_rings = adapter->drv_sds_rings;
	u8 drv_tx_rings = adapter->drv_tx_rings;
	u32 data;
	u16 intrpt_id, id;
	int ret;

	if (test_bit(__QLCNIC_RESETTING, &adapter->state)) {
		netdev_info(netdev, "Device is resetting\n");
		return -EBUSY;
	}

	if (qlcnic_get_diag_lock(adapter)) {
		netdev_info(netdev, "Device in diagnostics mode\n");
		return -EBUSY;
	}

	ret = qlcnic_83xx_diag_alloc_res(netdev, QLCNIC_INTERRUPT_TEST,
					 drv_sds_rings);
	if (ret)
		goto fail_diag_irq;

	ahw->diag_cnt = 0;
	ret = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_INTRPT_TEST);
	if (ret)
		goto fail_diag_irq;

	if (adapter->flags & QLCNIC_MSIX_ENABLED)
		intrpt_id = ahw->intr_tbl[0].id;
	else
		intrpt_id = QLCRDX(ahw, QLCNIC_DEF_INT_ID);

	cmd.req.arg[1] = 1;
	cmd.req.arg[2] = intrpt_id;
	cmd.req.arg[3] = BIT_0;

	ret = qlcnic_issue_cmd(adapter, &cmd);
	data = cmd.rsp.arg[2];
	id = LSW(data);
	val = LSB(MSW(data));
	if (id != intrpt_id)
		dev_info(&adapter->pdev->dev,
			 "Interrupt generated: 0x%x, requested:0x%x\n",
			 id, intrpt_id);
	if (val)
		dev_err(&adapter->pdev->dev,
			 "Interrupt test error: 0x%x\n", val);
	if (ret)
		goto done;

	msleep(20);
	ret = !ahw->diag_cnt;

done:
	qlcnic_free_mbx_args(&cmd);
	qlcnic_83xx_diag_free_res(netdev, drv_sds_rings);

fail_diag_irq:
	adapter->drv_sds_rings = drv_sds_rings;
	adapter->drv_tx_rings = drv_tx_rings;
	qlcnic_release_diag_lock(adapter);
	return ret;
}
