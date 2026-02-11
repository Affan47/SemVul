igb_force_mac_fc(struct e1000_hw *hw)
{
	u32 ctrl;
	s32 ret_val = 0;

	ctrl = rd32(E1000_CTRL);


	hw_dbg("hw->fc.current_mode = %u\n", hw->fc.current_mode);

	switch (hw->fc.current_mode) {
	case e1000_fc_none:
		ctrl &= (~(E1000_CTRL_TFCE | E1000_CTRL_RFCE));
		break;
	case e1000_fc_rx_pause:
		ctrl &= (~E1000_CTRL_TFCE);
		ctrl |= E1000_CTRL_RFCE;
		break;
	case e1000_fc_tx_pause:
		ctrl &= (~E1000_CTRL_RFCE);
		ctrl |= E1000_CTRL_TFCE;
		break;
	case e1000_fc_full:
		ctrl |= (E1000_CTRL_TFCE | E1000_CTRL_RFCE);
		break;
	default:
		hw_dbg("Flow control param set incorrectly\n");
		ret_val = -E1000_ERR_CONFIG;
		goto out;
	}

	wr32(E1000_CTRL, ctrl);

out:
	return ret_val;
}
