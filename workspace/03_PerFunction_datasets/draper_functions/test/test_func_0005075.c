hns_mac_get_info(struct hns_mac_cb *mac_cb,
			     struct device_node *np, u32 mac_mode_idx)
{
	mac_cb->link = false;
	mac_cb->half_duplex = false;
	mac_cb->speed = mac_phy_to_speed[mac_cb->phy_if];
	mac_cb->max_speed = mac_cb->speed;

	if (mac_cb->phy_if == PHY_INTERFACE_MODE_SGMII) {
		mac_cb->if_support = MAC_GMAC_SUPPORTED;
		mac_cb->if_support |= SUPPORTED_1000baseT_Full;
	} else if (mac_cb->phy_if == PHY_INTERFACE_MODE_XGMII) {
		mac_cb->if_support = SUPPORTED_10000baseR_FEC;
		mac_cb->if_support |= SUPPORTED_10000baseKR_Full;
	}

	mac_cb->max_frm = MAC_DEFAULT_MTU;
	mac_cb->tx_pause_frm_time = MAC_DEFAULT_PAUSE_TIME;


	mac_cb->phy_node = of_parse_phandle(np, "phy-handle", mac_cb->mac_id);
	if (mac_cb->phy_node)
		dev_dbg(mac_cb->dev, "mac%d phy_node: %s\n",
			mac_cb->mac_id, mac_cb->phy_node->name);
}
