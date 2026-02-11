qlcnic_initialize_nic(struct qlcnic_adapter *adapter)
{
	struct qlcnic_info nic_info;
	int err = 0;

	memset(&nic_info, 0, sizeof(struct qlcnic_info));
	err = qlcnic_get_nic_info(adapter, &nic_info, adapter->ahw->pci_func);
	if (err)
		return err;

	adapter->ahw->physical_port = (u8)nic_info.phys_port;
	adapter->ahw->switch_mode = nic_info.switch_mode;
	adapter->ahw->max_tx_ques = nic_info.max_tx_ques;
	adapter->ahw->max_rx_ques = nic_info.max_rx_ques;
	adapter->ahw->capabilities = nic_info.capabilities;

	if (adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_MORE_CAPS) {
		u32 temp;
		temp = QLCRD32(adapter, CRB_FW_CAPABILITIES_2, &err);
		if (err == -EIO)
			return err;
		adapter->ahw->extra_capability[0] = temp;
	} else {
		adapter->ahw->extra_capability[0] = 0;
	}

	adapter->ahw->max_mac_filters = nic_info.max_mac_filters;
	adapter->ahw->max_mtu = nic_info.max_mtu;

	if (adapter->ahw->capabilities & BIT_6) {
		adapter->flags |= QLCNIC_ESWITCH_ENABLED;
		adapter->ahw->nic_mode = QLCNIC_VNIC_MODE;
		adapter->max_tx_rings = QLCNIC_MAX_HW_VNIC_TX_RINGS;
		adapter->max_sds_rings = QLCNIC_MAX_VNIC_SDS_RINGS;

		dev_info(&adapter->pdev->dev, "vNIC mode enabled.\n");
	} else {
		adapter->ahw->nic_mode = QLCNIC_DEFAULT_MODE;
		adapter->max_tx_rings = QLCNIC_MAX_HW_TX_RINGS;
		adapter->max_sds_rings = QLCNIC_MAX_SDS_RINGS;
		adapter->flags &= ~QLCNIC_ESWITCH_ENABLED;
	}

	return err;
}
