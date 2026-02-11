e1000e_get_phy_info_m88(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32  ret_val;
	u16 phy_data;
	bool link;

	if (phy->media_type != e1000_media_type_copper) {
		e_dbg("Phy info is only valid for copper media\n");
		ret_val = -E1000_ERR_CONFIG;
		goto out;
	}

	ret_val = e1000e_phy_has_link_generic(hw, 1, 0, &link);
	if (ret_val)
		goto out;

	if (!link) {
		e_dbg("Phy info is only valid if link is up\n");
		ret_val = -E1000_ERR_CONFIG;
		goto out;
	}

	ret_val = e1e_rphy(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	if (ret_val)
		goto out;

	phy->polarity_correction = (phy_data & M88E1000_PSCR_POLARITY_REVERSAL)
	                           ? true : false;

	ret_val = e1000e_check_polarity_m88(hw);
	if (ret_val)
		goto out;

	ret_val = e1e_rphy(hw, M88E1000_PHY_SPEC_STATUS, &phy_data);
	if (ret_val)
		goto out;

	phy->is_mdix = (phy_data & M88E1000_PSSR_MDIX) ? true : false;

	if ((phy_data & M88E1000_PSSR_SPEED) == M88E1000_PSSR_1000MBS) {
#if 0
		ret_val = e1000e_get_cable_length(hw);
#endif
		ret_val = -E1000_ERR_CONFIG;
		if (ret_val)
			goto out;
#if 0
		ret_val = e1e_rphy(hw, PHY_1000T_STATUS, &phy_data);
		if (ret_val)
			goto out;

		phy->local_rx = (phy_data & SR_1000T_LOCAL_RX_STATUS)
		                ? e1000_1000t_rx_status_ok
		                : e1000_1000t_rx_status_not_ok;

		phy->remote_rx = (phy_data & SR_1000T_REMOTE_RX_STATUS)
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
