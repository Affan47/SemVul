e1000_commit_fc_settings_generic(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 txcw;


	switch (hw->fc.current_mode) {
	case e1000_fc_none:

		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD);
		break;
	case e1000_fc_rx_pause:


		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_PAUSE_MASK);
		break;
	case e1000_fc_tx_pause:


		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_ASM_DIR);
		break;
	case e1000_fc_full:


		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_PAUSE_MASK);
		break;
	default:
		e_dbg("Flow control param set incorrectly\n");
		return -E1000_ERR_CONFIG;
	}

	ew32(TXCW, txcw);
	mac->txcw = txcw;

	return 0;
}
