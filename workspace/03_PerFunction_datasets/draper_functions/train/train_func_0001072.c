_rtl92de_update_rxsignalstatistics(struct ieee80211_hw *hw,
					       struct rtl_stats *pstats)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	int weighting = 0;

	if (rtlpriv->stats.recv_signal_power == 0)
		rtlpriv->stats.recv_signal_power = pstats->recvsignalpower;
	if (pstats->recvsignalpower > rtlpriv->stats.recv_signal_power)
		weighting = 5;
	else if (pstats->recvsignalpower < rtlpriv->stats.recv_signal_power)
		weighting = (-5);
	rtlpriv->stats.recv_signal_power = (rtlpriv->stats.recv_signal_power *
		5 + pstats->recvsignalpower + weighting) / 6;
}
