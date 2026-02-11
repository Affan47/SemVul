atl1_check_link(struct atl1_adapter *adapter)
{
	struct atl1_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	u32 ret_val;
	u16 speed, duplex, phy_data;
	int reconfig = 0;


	atl1_read_phy_reg(hw, MII_BMSR, &phy_data);
	atl1_read_phy_reg(hw, MII_BMSR, &phy_data);
	if (!(phy_data & BMSR_LSTATUS)) {

		if (netif_carrier_ok(netdev)) {

			if (netif_msg_link(adapter))
				dev_info(&adapter->pdev->dev, "link is down\n");
			adapter->link_speed = SPEED_0;
			netif_carrier_off(netdev);
		}
		return 0;
	}


	ret_val = atl1_get_speed_and_duplex(hw, &speed, &duplex);
	if (ret_val)
		return ret_val;

	switch (hw->media_type) {
	case MEDIA_TYPE_1000M_FULL:
		if (speed != SPEED_1000 || duplex != FULL_DUPLEX)
			reconfig = 1;
		break;
	case MEDIA_TYPE_100M_FULL:
		if (speed != SPEED_100 || duplex != FULL_DUPLEX)
			reconfig = 1;
		break;
	case MEDIA_TYPE_100M_HALF:
		if (speed != SPEED_100 || duplex != HALF_DUPLEX)
			reconfig = 1;
		break;
	case MEDIA_TYPE_10M_FULL:
		if (speed != SPEED_10 || duplex != FULL_DUPLEX)
			reconfig = 1;
		break;
	case MEDIA_TYPE_10M_HALF:
		if (speed != SPEED_10 || duplex != HALF_DUPLEX)
			reconfig = 1;
		break;
	}


	if (!reconfig) {
		if (adapter->link_speed != speed ||
		    adapter->link_duplex != duplex) {
			adapter->link_speed = speed;
			adapter->link_duplex = duplex;
			atl1_setup_mac_ctrl(adapter);
			if (netif_msg_link(adapter))
				dev_info(&adapter->pdev->dev,
					"%s link is up %d Mbps %s\n",
					netdev->name, adapter->link_speed,
					adapter->link_duplex == FULL_DUPLEX ?
					"full duplex" : "half duplex");
		}
		if (!netif_carrier_ok(netdev)) {

			netif_carrier_on(netdev);
		}
		return 0;
	}


	if (netif_carrier_ok(netdev)) {
		adapter->link_speed = SPEED_0;
		netif_carrier_off(netdev);
		netif_stop_queue(netdev);
	}

	if (hw->media_type != MEDIA_TYPE_AUTO_SENSOR &&
	    hw->media_type != MEDIA_TYPE_1000M_FULL) {
		switch (hw->media_type) {
		case MEDIA_TYPE_100M_FULL:
			phy_data = MII_CR_FULL_DUPLEX | MII_CR_SPEED_100 |
			           MII_CR_RESET;
			break;
		case MEDIA_TYPE_100M_HALF:
			phy_data = MII_CR_SPEED_100 | MII_CR_RESET;
			break;
		case MEDIA_TYPE_10M_FULL:
			phy_data =
			    MII_CR_FULL_DUPLEX | MII_CR_SPEED_10 | MII_CR_RESET;
			break;
		default:

			phy_data = MII_CR_SPEED_10 | MII_CR_RESET;
			break;
		}
		atl1_write_phy_reg(hw, MII_BMCR, phy_data);
		return 0;
	}


	if (!adapter->phy_timer_pending) {
		adapter->phy_timer_pending = true;
		mod_timer(&adapter->phy_config_timer,
			  round_jiffies(jiffies + 3 * HZ));
	}

	return 0;
}
