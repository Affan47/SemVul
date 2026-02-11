rtl92c_phy_lc_calibrate(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	if (IS_92C_SERIAL(rtlhal->version))
		rtlpriv->cfg->ops->phy_lc_calibrate(hw, true);
	else
		rtlpriv->cfg->ops->phy_lc_calibrate(hw, false);
}
