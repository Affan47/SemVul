qlcnic_83xx_init_non_privileged_vnic(struct qlcnic_adapter *adapter)
{
	int err = -EIO;

	qlcnic_83xx_get_fw_version(adapter);
	if (qlcnic_set_eswitch_port_config(adapter))
		return err;

	if (qlcnic_83xx_get_port_info(adapter))
		return err;

	qlcnic_83xx_config_vnic_buff_descriptors(adapter);
	adapter->ahw->msix_supported = !!qlcnic_use_msi_x;
	adapter->flags |= QLCNIC_ADAPTER_INITIALIZED;

	dev_info(&adapter->pdev->dev, "HAL Version: %d, Virtual function\n",
		 adapter->ahw->fw_hal_version);

	return 0;
}
