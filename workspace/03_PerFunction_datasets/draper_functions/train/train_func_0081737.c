_rtl92s_phy_get_txpower_index(struct ieee80211_hw *hw, u8 channel,
					  u8 *cckpowerlevel, u8 *ofdmpowerLevel)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 index = (channel - 1);


	cckpowerlevel[0] = rtlefuse->txpwrlevel_cck[0][index];

	cckpowerlevel[1] = rtlefuse->txpwrlevel_cck[1][index];


	if (rtlphy->rf_type == RF_1T2R || rtlphy->rf_type == RF_1T1R) {

		ofdmpowerLevel[0] = rtlefuse->txpwrlevel_ht40_1s[0][index];
		ofdmpowerLevel[1] = rtlefuse->txpwrlevel_ht40_1s[1][index];
	} else if (rtlphy->rf_type == RF_2T2R) {

		ofdmpowerLevel[0] = rtlefuse->txpwrlevel_ht40_2s[0][index];
		ofdmpowerLevel[1] = rtlefuse->txpwrlevel_ht40_2s[1][index];
	} else {
		ofdmpowerLevel[0] = 0;
		ofdmpowerLevel[1] = 0;
	}
}
