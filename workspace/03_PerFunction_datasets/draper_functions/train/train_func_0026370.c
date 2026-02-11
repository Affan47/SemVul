ixgbe_setup_mac_link_smartspeed(struct ixgbe_hw *hw,
				     ixgbe_link_speed speed,
				     bool autoneg_wait_to_complete)
{
	s32 status = 0;
	ixgbe_link_speed link_speed = IXGBE_LINK_SPEED_UNKNOWN;
	s32 i, j;
	bool link_up = false;
	u32 autoc_reg = IXGBE_READ_REG(hw, IXGBE_AUTOC);


	hw->phy.autoneg_advertised = 0;

	if (speed & IXGBE_LINK_SPEED_10GB_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_10GB_FULL;

	if (speed & IXGBE_LINK_SPEED_1GB_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_1GB_FULL;

	if (speed & IXGBE_LINK_SPEED_100_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_100_FULL;


	hw->phy.smart_speed_active = false;
	for (j = 0; j < IXGBE_SMARTSPEED_MAX_RETRIES; j++) {
		status = ixgbe_setup_mac_link_82599(hw, speed,
						    autoneg_wait_to_complete);
		if (status != 0)
			goto out;


		for (i = 0; i < 5; i++) {
			mdelay(100);


			status = hw->mac.ops.check_link(hw, &link_speed,
							&link_up, false);
			if (status != 0)
				goto out;

			if (link_up)
				goto out;
		}
	}


	if (((autoc_reg & IXGBE_AUTOC_KR_SUPP) == 0) ||
	    ((autoc_reg & IXGBE_AUTOC_KX4_KX_SUPP_MASK) == 0))
		goto out;


	hw->phy.smart_speed_active = true;
	status = ixgbe_setup_mac_link_82599(hw, speed,
					    autoneg_wait_to_complete);
	if (status != 0)
		goto out;


	for (i = 0; i < 6; i++) {
		mdelay(100);


		status = hw->mac.ops.check_link(hw, &link_speed,
						&link_up, false);
		if (status != 0)
			goto out;

		if (link_up)
			goto out;
	}


	hw->phy.smart_speed_active = false;
	status = ixgbe_setup_mac_link_82599(hw, speed,
					    autoneg_wait_to_complete);

out:
	if (link_up && (link_speed == IXGBE_LINK_SPEED_1GB_FULL))
		hw_dbg(hw, "Smartspeed has downgraded the link speed from the maximum advertised\n");
	return status;
}
