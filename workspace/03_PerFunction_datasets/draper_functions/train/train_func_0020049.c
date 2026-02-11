_rtl92s_dm_init_dynamic_txpower(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if ((hal_get_firmwareversion(rtlpriv) >= 60) &&
	    (rtlpriv->dm.dm_type == DM_TYPE_BYDRIVER))
		rtlpriv->dm.dynamic_txpower_enable = true;
	else
		rtlpriv->dm.dynamic_txpower_enable = false;

	rtlpriv->dm.last_dtp_lvl = TX_HIGHPWR_LEVEL_NORMAL;
	rtlpriv->dm.dynamic_txhighpower_lvl = TX_HIGHPWR_LEVEL_NORMAL;
}
