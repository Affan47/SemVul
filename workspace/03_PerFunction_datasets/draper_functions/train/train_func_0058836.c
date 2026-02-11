_rtl8821ae_set_ra_vht_ratr_bitmap(struct ieee80211_hw *hw,
					     enum wireless_mode wirelessmode,
					     u32 ratr_bitmap)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u32 ret_bitmap = ratr_bitmap;

	if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40
		|| rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80)
		ret_bitmap = ratr_bitmap;
	else if (wirelessmode == WIRELESS_MODE_AC_5G
		|| wirelessmode == WIRELESS_MODE_AC_24G) {
		if (rtlphy->rf_type == RF_1T1R)
			ret_bitmap = ratr_bitmap & (~BIT21);
		else
			ret_bitmap = ratr_bitmap & (~(BIT31|BIT21));
	}

	return ret_bitmap;
}
