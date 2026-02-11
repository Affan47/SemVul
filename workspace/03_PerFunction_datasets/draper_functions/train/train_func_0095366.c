igb_get_phy_info_igp(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;
	bool link;

	DEBUGFUNC("igb_get_phy_info_igp");

	ret_val = igb_phy_has_link_generic(hw, 1, 0, &link);
	if (ret_val)
		goto out;

	if (!link) {
		DEBUGOUT("Phy info is only valid if link is up\n");
		ret_val = -E1000_ERR_CONFIG;
		goto out;
	}

	phy->polarity_correction = true;

	ret_val = igb_check_polarity_igp(hw);
	if (ret_val)
		goto out;

	ret_val = phy->ops.read_reg(hw, IGP01E1000_PHY_PORT_STATUS, &data);
	if (ret_val)
		goto out;

	phy->is_mdix = (data & IGP01E1000_PSSR_MDIX) ? true : false;

	if ((data & IGP01E1000_PSSR_SPEED_MASK) ==
	    IGP01E1000_PSSR_SPEED_1000MBPS) {
#if 0
		ret_val = phy->ops.get_cable_length(hw);
#endif
		ret_val = -E1000_ERR_CONFIG;
		if (ret_val)
			goto out;
#if 0
		ret_val = phy->ops.read_reg(hw, PHY_1000T_STATUS, &data);
		if (ret_val)
			goto out;

		phy->local_rx = (data & SR_1000T_LOCAL_RX_STATUS)
		                ? e1000_1000t_rx_status_ok
		                : e1000_1000t_rx_status_not_ok;

		phy->remote_rx = (data & SR_1000T_REMOTE_RX_STATUS)
		                 ? e1000_1000t_rx_status_ok
		                 : e1000_1000t_rx_status_not_ok;
#endif
	} else {
		phy->cable_length = E1000_CABLE_LENGTH_UNDEFINED;
		phy->local_rx = e1000_1000t_rx_status_undefined;
		phy->remote_rx = e1000_1000t_rx_status_undefined;
	}

out:
	return ret_val;
}
