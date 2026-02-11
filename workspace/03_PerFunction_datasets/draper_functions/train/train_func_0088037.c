ixgbe_setup_internal_phy_t_x550em(struct ixgbe_hw *hw)
{
	ixgbe_link_speed force_speed;
	bool link_up;
	u32 status;
	u16 speed;

	if (hw->mac.ops.get_media_type(hw) != ixgbe_media_type_copper)
		return IXGBE_ERR_CONFIG;

	if (hw->phy.nw_mng_if_sel & IXGBE_NW_MNG_IF_SEL_INT_PHY_MODE) {
		speed = IXGBE_LINK_SPEED_10GB_FULL |
			IXGBE_LINK_SPEED_1GB_FULL;
		return ixgbe_setup_kr_speed_x550em(hw, speed);
	}


	status = ixgbe_ext_phy_t_x550em_get_link(hw, &link_up);
	if (status)
		return status;

	if (!link_up)
		return 0;

	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_AUTO_NEG_VENDOR_STAT,
				      IXGBE_MDIO_AUTO_NEG_DEV_TYPE,
				      &speed);
	if (status)
		return status;


	status = ixgbe_ext_phy_t_x550em_get_link(hw, &link_up);
	if (status)
		return status;

	if (!link_up)
		return 0;


	speed &= IXGBE_MDIO_AUTO_NEG_VENDOR_STATUS_MASK;

	switch (speed) {
	case IXGBE_MDIO_AUTO_NEG_VENDOR_STATUS_10GB_FULL:
		force_speed = IXGBE_LINK_SPEED_10GB_FULL;
		break;
	case IXGBE_MDIO_AUTO_NEG_VENDOR_STATUS_1GB_FULL:
		force_speed = IXGBE_LINK_SPEED_1GB_FULL;
		break;
	default:

		return IXGBE_ERR_INVALID_LINK_SETTINGS;
	}

	return ixgbe_setup_ixfi_x550em(hw, &force_speed);
}
