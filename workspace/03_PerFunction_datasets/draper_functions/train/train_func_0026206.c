rtl92ee_dm_write_dig(struct ieee80211_hw *hw, u8 current_igi)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_dig = &rtlpriv->dm_digtable;

	if (dm_dig->stop_dig)
		return;

	if (dm_dig->cur_igvalue != current_igi) {
		rtl_set_bbreg(hw, ROFDM0_XAAGCCORE1, 0x7f, current_igi);
		if (rtlpriv->phy.rf_type != RF_1T1R)
			rtl_set_bbreg(hw, ROFDM0_XBAGCCORE1, 0x7f, current_igi);
	}
	dm_dig->pre_igvalue = dm_dig->cur_igvalue;
	dm_dig->cur_igvalue = current_igi;
}
