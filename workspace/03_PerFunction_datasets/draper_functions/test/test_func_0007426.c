e1000_cfg_on_link_up_80003es2lan(struct e1000_hw *hw)
{
	s32 ret_val = 0;
	u16 speed;
	u16 duplex;

	if (hw->phy.media_type == e1000_media_type_copper) {
		ret_val = e1000e_get_speed_and_duplex_copper(hw, &speed,
							     &duplex);
		if (ret_val)
			return ret_val;

		if (speed == SPEED_1000)
			ret_val = e1000_cfg_kmrn_1000_80003es2lan(hw);
		else
			ret_val = e1000_cfg_kmrn_10_100_80003es2lan(hw, duplex);
	}

	return ret_val;
}
