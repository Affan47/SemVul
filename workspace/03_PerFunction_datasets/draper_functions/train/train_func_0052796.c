ixgbe_reset_phy_generic(struct ixgbe_hw *hw)
{
	u32 i;
	u16 ctrl = 0;
	s32 status = 0;

	if (hw->phy.type == ixgbe_phy_unknown)
		status = ixgbe_identify_phy_generic(hw);

	if (status != 0 || hw->phy.type == ixgbe_phy_none)
		return status;


	if (!hw->phy.reset_if_overtemp &&
	    (IXGBE_ERR_OVERTEMP == hw->phy.ops.check_overtemp(hw)))
		return 0;


	if (ixgbe_check_reset_blocked(hw))
		return 0;


	hw->phy.ops.write_reg(hw, MDIO_CTRL1,
			      MDIO_MMD_PHYXS,
			      MDIO_CTRL1_RESET);


	for (i = 0; i < 30; i++) {
		msleep(100);
		hw->phy.ops.read_reg(hw, MDIO_CTRL1,
				     MDIO_MMD_PHYXS, &ctrl);
		if (!(ctrl & MDIO_CTRL1_RESET)) {
			udelay(2);
			break;
		}
	}

	if (ctrl & MDIO_CTRL1_RESET) {
		hw_dbg(hw, "PHY reset polling failed to complete.\n");
		return IXGBE_ERR_RESET_FAILED;
	}

	return 0;
}
