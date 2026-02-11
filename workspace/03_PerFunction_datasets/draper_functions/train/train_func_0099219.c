igb_get_link_up_info_82575(struct e1000_hw *hw, u16 *speed,
					u16 *duplex)
{
	s32 ret_val;

	if (hw->phy.media_type != e1000_media_type_copper)
		ret_val = igb_get_pcs_speed_and_duplex_82575(hw, speed,
							       duplex);
	else
		ret_val = igb_get_speed_and_duplex_copper(hw, speed,
								    duplex);

	return ret_val;
}
