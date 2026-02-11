e1000_get_link_up_info_vf(struct e1000_hw *hw, u16 *speed,
				     u16 *duplex)
{
	s32 status;

	status = er32(STATUS);
	if (status & E1000_STATUS_SPEED_1000)
		*speed = SPEED_1000;
	else if (status & E1000_STATUS_SPEED_100)
		*speed = SPEED_100;
	else
		*speed = SPEED_10;

	if (status & E1000_STATUS_FD)
		*duplex = FULL_DUPLEX;
	else
		*duplex = HALF_DUPLEX;

	return E1000_SUCCESS;
}
