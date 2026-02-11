rtl92ee_phy_set_txpower_level(struct ieee80211_hw *hw, u8 channel)
{
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_phy *rtlphy = &rtl_priv(hw)->phy;
	enum radio_path rfpath;

	if (!rtlefuse->txpwr_fromeprom)
		return;
	for (rfpath = RF90_PATH_A; rfpath < rtlphy->num_total_rfpath;
	     rfpath++) {
		phy_set_txpower_index_by_rate_section(hw, rfpath,
						      channel, CCK);
		phy_set_txpower_index_by_rate_section(hw, rfpath,
						      channel, OFDM);
		phy_set_txpower_index_by_rate_section(hw, rfpath,
						      channel,
						      HT_MCS0_MCS7);

		if (rtlphy->num_total_rfpath >= 2)
			phy_set_txpower_index_by_rate_section(hw,
							      rfpath, channel,
							      HT_MCS8_MCS15);
	}
}
