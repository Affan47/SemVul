phy_set_txpower_index_by_rate_section(struct ieee80211_hw *hw,
						  enum radio_path rfpath,
						  u8 channel,
						  enum rate_section section)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	struct rtl_phy *rtlphy = &rtlpriv->phy;

	if (section == CCK) {
		u8 cck_rates[] = {DESC92C_RATE1M, DESC92C_RATE2M,
				  DESC92C_RATE5_5M, DESC92C_RATE11M};
		if (rtlhal->current_bandtype == BAND_ON_2_4G)
			phy_set_txpower_index_by_rate_array(hw, rfpath,
							rtlphy->current_chan_bw,
							channel, cck_rates, 4);
	} else if (section == OFDM) {
		u8 ofdm_rates[] = {DESC92C_RATE6M, DESC92C_RATE9M,
				   DESC92C_RATE12M, DESC92C_RATE18M,
				   DESC92C_RATE24M, DESC92C_RATE36M,
				   DESC92C_RATE48M, DESC92C_RATE54M};
		phy_set_txpower_index_by_rate_array(hw, rfpath,
						    rtlphy->current_chan_bw,
						    channel, ofdm_rates, 8);
	} else if (section == HT_MCS0_MCS7) {
		u8 ht_rates1t[]  = {DESC92C_RATEMCS0, DESC92C_RATEMCS1,
				    DESC92C_RATEMCS2, DESC92C_RATEMCS3,
				    DESC92C_RATEMCS4, DESC92C_RATEMCS5,
				    DESC92C_RATEMCS6, DESC92C_RATEMCS7};
		phy_set_txpower_index_by_rate_array(hw, rfpath,
						    rtlphy->current_chan_bw,
						    channel, ht_rates1t, 8);
	} else if (section == HT_MCS8_MCS15) {
		u8 ht_rates2t[]  = {DESC92C_RATEMCS8, DESC92C_RATEMCS9,
				    DESC92C_RATEMCS10, DESC92C_RATEMCS11,
				    DESC92C_RATEMCS12, DESC92C_RATEMCS13,
				    DESC92C_RATEMCS14, DESC92C_RATEMCS15};
		phy_set_txpower_index_by_rate_array(hw, rfpath,
						    rtlphy->current_chan_bw,
						    channel, ht_rates2t, 8);
	} else
		RT_TRACE(rtlpriv, FPHY, PHY_TXPWR,
			 "Invalid RateSection %d\n", section);
}
