at91_can_id_to_reg_mid(canid_t can_id)
{
	u32 reg_mid;

	if (can_id & CAN_EFF_FLAG)
		reg_mid = (can_id & CAN_EFF_MASK) | AT91_MID_MIDE;
	else
		reg_mid = (can_id & CAN_SFF_MASK) << 18;

	return reg_mid;
}
