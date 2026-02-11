be_setup(struct be_adapter *adapter)
{
	struct device *dev = &adapter->pdev->dev;
	u32 en_flags;
	int status;

	status = be_func_init(adapter);
	if (status)
		return status;

	be_setup_init(adapter);

	if (!lancer_chip(adapter))
		be_cmd_req_native_mode(adapter);


	status = be_cmd_get_cntl_attributes(adapter);
	if (status)
		return status;

	if (!BE2_chip(adapter) && be_physfn(adapter))
		be_alloc_sriov_res(adapter);

	status = be_get_config(adapter);
	if (status)
		goto err;

	status = be_msix_enable(adapter);
	if (status)
		goto err;


	en_flags = BE_IF_FLAGS_RSS | BE_IF_FLAGS_DEFQ_RSS;
	en_flags = en_flags & be_if_cap_flags(adapter);
	status = be_cmd_if_create(adapter, be_if_cap_flags(adapter), en_flags,
				  &adapter->if_handle, 0);
	if (status)
		goto err;


	rtnl_lock();
	status = be_setup_queues(adapter);
	rtnl_unlock();
	if (status)
		goto err;

	be_cmd_get_fn_privileges(adapter, &adapter->cmd_privileges, 0);

	status = be_mac_setup(adapter);
	if (status)
		goto err;

	be_cmd_get_fw_ver(adapter);
	dev_info(dev, "FW version is %s\n", adapter->fw_ver);

	if (BE2_chip(adapter) && fw_major_num(adapter->fw_ver) < 4) {
		dev_err(dev, "Firmware on card is old(%s), IRQs may not work",
			adapter->fw_ver);
		dev_err(dev, "Please upgrade firmware to version >= 4.0\n");
	}

	status = be_cmd_set_flow_control(adapter, adapter->tx_fc,
					 adapter->rx_fc);
	if (status)
		be_cmd_get_flow_control(adapter, &adapter->tx_fc,
					&adapter->rx_fc);

	dev_info(&adapter->pdev->dev, "HW Flow control - TX:%d RX:%d\n",
		 adapter->tx_fc, adapter->rx_fc);

	if (be_physfn(adapter))
		be_cmd_set_logical_link_config(adapter,
					       IFLA_VF_LINK_STATE_AUTO, 0);

	if (adapter->num_vfs)
		be_vf_setup(adapter);

	status = be_cmd_get_phy_info(adapter);
	if (!status && be_pause_supported(adapter))
		adapter->phy.fc_autoneg = 1;

	be_schedule_worker(adapter);
	adapter->flags |= BE_FLAGS_SETUP_DONE;
	return 0;
err:
	be_clear(adapter);
	return status;
}
