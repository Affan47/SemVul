rtl8723be_dm_init_txpower_tracking(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.txpower_tracking = true;
	rtlpriv->dm.txpower_track_control = true;
	rtlpriv->dm.thermalvalue = 0;

	rtlpriv->dm.ofdm_index[0] = 30;
	rtlpriv->dm.cck_index = 20;

	rtlpriv->dm.swing_idx_cck_base = rtlpriv->dm.cck_index;

	rtlpriv->dm.swing_idx_ofdm_base[0] = rtlpriv->dm.ofdm_index[0];
	rtlpriv->dm.delta_power_index[RF90_PATH_A] = 0;
	rtlpriv->dm.delta_power_index_last[RF90_PATH_A] = 0;
	rtlpriv->dm.power_index_offset[RF90_PATH_A] = 0;

	RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		 "  rtlpriv->dm.txpower_tracking = %d\n",
		  rtlpriv->dm.txpower_tracking);
}
