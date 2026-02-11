_rtl8821ae_phy_txpower_training_by_path(struct ieee80211_hw *hw,
						    u8 bw, u8 channel, u8 path)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;

	u8 i;
	u32 power_level, data, offset;

	if (path >= rtlphy->num_total_rfpath)
		return;

	data = 0;
	if (path == RF90_PATH_A) {
		power_level =
			_rtl8821ae_get_txpower_index(hw, RF90_PATH_A,
			DESC_RATEMCS7, bw, channel);
		offset =  RA_TXPWRTRAING;
	} else {
		power_level =
			_rtl8821ae_get_txpower_index(hw, RF90_PATH_B,
			DESC_RATEMCS7, bw, channel);
		offset =  RB_TXPWRTRAING;
	}

	for (i = 0; i < 3; i++) {
		if (i == 0)
			power_level = power_level - 10;
		else if (i == 1)
			power_level = power_level - 8;
		else
			power_level = power_level - 6;

		data |= (((power_level > 2) ? (power_level) : 2) << (i * 8));
	}
	rtl_set_bbreg(hw, offset, 0xffffff, data);
}
