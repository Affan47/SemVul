ixgb_sw_init(struct ixgb_adapter *adapter)
{
	struct ixgb_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;


	hw->vendor_id = pdev->vendor;
	hw->device_id = pdev->device;
	hw->subsystem_vendor_id = pdev->subsystem_vendor;
	hw->subsystem_id = pdev->subsystem_device;

	hw->max_frame_size = netdev->mtu + ENET_HEADER_SIZE + ENET_FCS_LENGTH;
	adapter->rx_buffer_len = hw->max_frame_size + 8;

	if ((hw->device_id == IXGB_DEVICE_ID_82597EX) ||
	    (hw->device_id == IXGB_DEVICE_ID_82597EX_CX4) ||
	    (hw->device_id == IXGB_DEVICE_ID_82597EX_LR) ||
	    (hw->device_id == IXGB_DEVICE_ID_82597EX_SR))
		hw->mac_type = ixgb_82597;
	else {

		netif_err(adapter, probe, adapter->netdev, "unsupported device id\n");
	}


	hw->fc.send_xon = 1;

	set_bit(__IXGB_DOWN, &adapter->flags);
	return 0;
}
