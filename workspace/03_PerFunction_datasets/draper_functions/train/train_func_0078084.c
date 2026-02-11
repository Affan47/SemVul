e1000_print_device_info(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	u32 ret_val;
	u8 pba_str[E1000_PBANUM_LENGTH];


	e_info("(PCI Express:2.5GT/s:%s) %pM\n",

	       ((hw->bus.width == e1000_bus_width_pcie_x4) ? "Width x4" :
		"Width x1"),

	       netdev->dev_addr);
	e_info("Intel(R) PRO/%s Network Connection\n",
	       (hw->phy.type == e1000_phy_ife) ? "10/100" : "1000");
	ret_val = e1000_read_pba_string_generic(hw, pba_str,
						E1000_PBANUM_LENGTH);
	if (ret_val)
		strlcpy((char *)pba_str, "Unknown", sizeof(pba_str));
	e_info("MAC: %d, PHY: %d, PBA No: %s\n",
	       hw->mac.type, hw->phy.type, pba_str);
}
