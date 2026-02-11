_rtl88e_phy_bb8188e_config_parafile(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	bool rtstatus;

	rtstatus = phy_config_bb_with_headerfile(hw, BASEBAND_CONFIG_PHY_REG);
	if (!rtstatus) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG, "Write BB Reg Fail!!");
		return false;
	}

	if (!rtlefuse->autoload_failflag) {
		rtlphy->pwrgroup_cnt = 0;
		rtstatus =
		  phy_config_bb_with_pghdr(hw, BASEBAND_CONFIG_PHY_REG);
	}
	if (!rtstatus) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG, "BB_PG Reg Fail!!");
		return false;
	}
	rtstatus =
	  phy_config_bb_with_headerfile(hw, BASEBAND_CONFIG_AGC_TAB);
	if (!rtstatus) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG, "AGC Table Fail\n");
		return false;
	}
	rtlphy->cck_high_power =
	  (bool)(rtl_get_bbreg(hw, RFPGA0_XA_HSSIPARAMETER2, 0x200));

	return true;
}
