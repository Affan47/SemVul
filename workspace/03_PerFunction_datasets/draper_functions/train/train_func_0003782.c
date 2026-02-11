_rtl8821ae_phy_set_txpower_level_by_path(struct ieee80211_hw *hw,
						     u8 *array, u8 path,
						     u8 channel, u8 size)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 i;
	u8 power_index;

	for (i = 0; i < size; i++) {
		power_index =
		  _rtl8821ae_get_txpower_index(hw, path, array[i],
					       rtlphy->current_chan_bw,
					       channel);
		_rtl8821ae_phy_set_txpower_index(hw, power_index, path,
						 array[i]);
	}
}
