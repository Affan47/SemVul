igb_power_up_link(struct igb_adapter *adapter)
{
	igb_reset_phy(&adapter->hw);

	if (adapter->hw.phy.media_type == e1000_media_type_copper)
		igb_power_up_phy_copper(&adapter->hw);
	else
		igb_power_up_serdes_link_82575(&adapter->hw);

	igb_setup_link(&adapter->hw);
}
