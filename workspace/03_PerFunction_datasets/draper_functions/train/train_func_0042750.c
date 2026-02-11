e1000_check_polarity_igp(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data, offset, mask;


	ret_val = e1e_rphy(hw, IGP01E1000_PHY_PORT_STATUS, &data);
	if (ret_val)
		return ret_val;

	if ((data & IGP01E1000_PSSR_SPEED_MASK) ==
	    IGP01E1000_PSSR_SPEED_1000MBPS) {
		offset = IGP01E1000_PHY_PCS_INIT_REG;
		mask = IGP01E1000_PHY_POLARITY_MASK;
	} else {


		offset = IGP01E1000_PHY_PORT_STATUS;
		mask = IGP01E1000_PSSR_POLARITY_REVERSED;
	}

	ret_val = e1e_rphy(hw, offset, &data);

	if (!ret_val)
		phy->cable_polarity = ((data & mask)
				       ? e1000_rev_polarity_reversed
				       : e1000_rev_polarity_normal);

	return ret_val;
}
