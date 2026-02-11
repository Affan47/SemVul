rtl8821ae_phy_iq_calibrate(struct ieee80211_hw *hw, bool b_recovery)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;

	if (!rtlphy->lck_inprogress) {
		spin_lock(&rtlpriv->locks.iqk_lock);
		rtlphy->lck_inprogress = true;
		spin_unlock(&rtlpriv->locks.iqk_lock);

		_rtl8821ae_phy_iq_calibrate(hw);

		spin_lock(&rtlpriv->locks.iqk_lock);
		rtlphy->lck_inprogress = false;
		spin_unlock(&rtlpriv->locks.iqk_lock);
	}
}
