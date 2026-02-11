e1000_set_d0_lplu_state_82571(struct e1000_hw *hw, bool active)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;

	ret_val = e1e_rphy(hw, IGP02E1000_PHY_POWER_MGMT, &data);
	if (ret_val)
		return ret_val;

	if (active) {
		data |= IGP02E1000_PM_D0_LPLU;
		ret_val = e1e_wphy(hw, IGP02E1000_PHY_POWER_MGMT, data);
		if (ret_val)
			return ret_val;


		ret_val = e1e_rphy(hw, IGP01E1000_PHY_PORT_CONFIG, &data);
		if (ret_val)
			return ret_val;
		data &= ~IGP01E1000_PSCFR_SMART_SPEED;
		ret_val = e1e_wphy(hw, IGP01E1000_PHY_PORT_CONFIG, data);
		if (ret_val)
			return ret_val;
	} else {
		data &= ~IGP02E1000_PM_D0_LPLU;
		ret_val = e1e_wphy(hw, IGP02E1000_PHY_POWER_MGMT, data);


		if (phy->smart_speed == e1000_smart_speed_on) {
			ret_val = e1e_rphy(hw, IGP01E1000_PHY_PORT_CONFIG,
					   &data);
			if (ret_val)
				return ret_val;

			data |= IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = e1e_wphy(hw, IGP01E1000_PHY_PORT_CONFIG,
					   data);
			if (ret_val)
				return ret_val;
		} else if (phy->smart_speed == e1000_smart_speed_off) {
			ret_val = e1e_rphy(hw, IGP01E1000_PHY_PORT_CONFIG,
					   &data);
			if (ret_val)
				return ret_val;

			data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = e1e_wphy(hw, IGP01E1000_PHY_PORT_CONFIG,
					   data);
			if (ret_val)
				return ret_val;
		}
	}

	return 0;
}
