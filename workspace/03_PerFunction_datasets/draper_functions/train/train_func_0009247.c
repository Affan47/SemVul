e1000e_poll_fiber_serdes_link_generic(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 i, status;
	s32 ret_val = E1000_SUCCESS;


	for (i = 0; i < FIBER_LINK_UP_LIMIT; i++) {
		msleep(10);
		status = er32(STATUS);
		if (status & E1000_STATUS_LU)
			break;
	}
	if (i == FIBER_LINK_UP_LIMIT) {
		e_dbg("Never got a valid link from auto-neg!!!\n");
		mac->autoneg_failed = 1;


		ret_val = hw->mac.ops.check_for_link(hw);
		if (ret_val) {
			e_dbg("Error while checking for link\n");
			goto out;
		}
		mac->autoneg_failed = 0;
	} else {
		mac->autoneg_failed = 0;
		e_dbg("Valid Link Found\n");
	}

out:
	return ret_val;
}
