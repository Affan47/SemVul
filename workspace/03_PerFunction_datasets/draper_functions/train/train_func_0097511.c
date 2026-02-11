igb_check_for_fiber_link_generic(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 rxcw;
	u32 ctrl;
	u32 status;
	s32 ret_val = E1000_SUCCESS;

	DEBUGFUNC("igb_check_for_fiber_link_generic");

	ctrl = E1000_READ_REG(hw, E1000_CTRL);
	status = E1000_READ_REG(hw, E1000_STATUS);
	rxcw = E1000_READ_REG(hw, E1000_RXCW);


	if ((ctrl & E1000_CTRL_SWDPIN1) && (!(status & E1000_STATUS_LU)) &&
	    (!(rxcw & E1000_RXCW_C))) {
		if (mac->autoneg_failed == 0) {
			mac->autoneg_failed = 1;
			goto out;
		}
		DEBUGOUT("NOT RXing /C/, disable AutoNeg and force link.\n");


		E1000_WRITE_REG(hw, E1000_TXCW, (mac->txcw & ~E1000_TXCW_ANE));


		ctrl = E1000_READ_REG(hw, E1000_CTRL);
		ctrl |= (E1000_CTRL_SLU | E1000_CTRL_FD);
		E1000_WRITE_REG(hw, E1000_CTRL, ctrl);


		ret_val = igb_config_fc_after_link_up_generic(hw);
		if (ret_val) {
			DEBUGOUT("Error configuring flow control\n");
			goto out;
		}
	} else if ((ctrl & E1000_CTRL_SLU) && (rxcw & E1000_RXCW_C)) {


		DEBUGOUT("RXing /C/, enable AutoNeg and stop forcing link.\n");
		E1000_WRITE_REG(hw, E1000_TXCW, mac->txcw);
		E1000_WRITE_REG(hw, E1000_CTRL, (ctrl & ~E1000_CTRL_SLU));

		mac->serdes_has_link = true;
	}

out:
	return ret_val;
}
