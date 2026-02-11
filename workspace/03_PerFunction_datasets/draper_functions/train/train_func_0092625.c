ixgbe_setup_phy_link_speed_generic(struct ixgbe_hw *hw,
				       ixgbe_link_speed speed,
				       bool autoneg_wait_to_complete)
{


	hw->phy.autoneg_advertised = 0;

	if (speed & IXGBE_LINK_SPEED_10GB_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_10GB_FULL;

	if (speed & IXGBE_LINK_SPEED_1GB_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_1GB_FULL;

	if (speed & IXGBE_LINK_SPEED_100_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_100_FULL;


	hw->phy.ops.setup_link(hw);

	return 0;
}
