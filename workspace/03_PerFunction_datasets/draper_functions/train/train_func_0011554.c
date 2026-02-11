rtl92d_dm_pwdb_monitor(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);


	if (rtlpriv->mac80211.opmode != NL80211_IFTYPE_STATION)
		return;

	if (rtlpriv->dm.useramask) {
		u32 temp = rtlpriv->dm.undec_sm_pwdb;

		temp <<= 16;
		temp |= 0x100;


		rtl92d_fill_h2c_cmd(hw, H2C_RSSI_REPORT, 3, (u8 *) (&temp));
	} else {
		rtl_write_byte(rtlpriv, 0x4fe,
			       (u8) rtlpriv->dm.undec_sm_pwdb);
	}
}
