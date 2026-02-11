rtl92s_phy_set_bw_mode(struct ieee80211_hw *hw,
			    enum nl80211_channel_type ch_type)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u8 reg_bw_opmode;

	RT_TRACE(rtlpriv, COMP_SCAN, DBG_TRACE, "Switch to %s bandwidth\n",
		 rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20 ?
		 "20MHz" : "40MHz");

	if (rtlphy->set_bwmode_inprogress)
		return;
	if (is_hal_stop(rtlhal))
		return;

	rtlphy->set_bwmode_inprogress = true;

	reg_bw_opmode = rtl_read_byte(rtlpriv, BW_OPMODE);

	rtl_read_byte(rtlpriv, RRSR + 2);

	switch (rtlphy->current_chan_bw) {
	case HT_CHANNEL_WIDTH_20:
		reg_bw_opmode |= BW_OPMODE_20MHZ;
		rtl_write_byte(rtlpriv, BW_OPMODE, reg_bw_opmode);
		break;
	case HT_CHANNEL_WIDTH_20_40:
		reg_bw_opmode &= ~BW_OPMODE_20MHZ;
		rtl_write_byte(rtlpriv, BW_OPMODE, reg_bw_opmode);
		break;
	default:
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
			 "unknown bandwidth: %#X\n", rtlphy->current_chan_bw);
		break;
	}

	switch (rtlphy->current_chan_bw) {
	case HT_CHANNEL_WIDTH_20:
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BRFMOD, 0x0);
		rtl_set_bbreg(hw, RFPGA1_RFMOD, BRFMOD, 0x0);

		if (rtlhal->version >= VERSION_8192S_BCUT)
			rtl_write_byte(rtlpriv, RFPGA0_ANALOGPARAMETER2, 0x58);
		break;
	case HT_CHANNEL_WIDTH_20_40:
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BRFMOD, 0x1);
		rtl_set_bbreg(hw, RFPGA1_RFMOD, BRFMOD, 0x1);

		rtl_set_bbreg(hw, RCCK0_SYSTEM, BCCK_SIDEBAND,
				(mac->cur_40_prime_sc >> 1));
		rtl_set_bbreg(hw, ROFDM1_LSTF, 0xC00, mac->cur_40_prime_sc);

		if (rtlhal->version >= VERSION_8192S_BCUT)
			rtl_write_byte(rtlpriv, RFPGA0_ANALOGPARAMETER2, 0x18);
		break;
	default:
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
			 "unknown bandwidth: %#X\n", rtlphy->current_chan_bw);
		break;
	}

	rtl92s_phy_rf6052_set_bandwidth(hw, rtlphy->current_chan_bw);
	rtlphy->set_bwmode_inprogress = false;
	RT_TRACE(rtlpriv, COMP_SCAN, DBG_TRACE, "<==\n");
}
