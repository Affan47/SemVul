rtl92c_dm_dig(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (rtlpriv->dm.dm_initialgain_enable == false)
		return;
	if (!(rtlpriv->dm.dm_flag & DYNAMIC_FUNC_DIG))
		return;

	rtl92c_dm_ctrl_initgain_by_twoport(hw);
}
