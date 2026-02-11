rtl8723e_read_eeprom_info(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 tmp_u1b;
	u32 value32;

	value32 = rtl_read_dword(rtlpriv, rtlpriv->cfg->maps[EFUSE_TEST]);
	value32 = (value32 & ~EFUSE_SEL_MASK) | EFUSE_SEL(EFUSE_WIFI_SEL_0);
	rtl_write_dword(rtlpriv, rtlpriv->cfg->maps[EFUSE_TEST], value32);

	rtlhal->version = _rtl8723e_read_chip_version(hw);

	if (get_rf_type(rtlphy) == RF_1T1R)
		rtlpriv->dm.rfpath_rxenable[0] = true;
	else
		rtlpriv->dm.rfpath_rxenable[0] =
		    rtlpriv->dm.rfpath_rxenable[1] = true;
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "VersionID = 0x%4x\n",
						rtlhal->version);

	tmp_u1b = rtl_read_byte(rtlpriv, REG_9346CR);
	if (tmp_u1b & BIT(4)) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG, "Boot from EEPROM\n");
		rtlefuse->epromtype = EEPROM_93C46;
	} else {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG, "Boot from EFUSE\n");
		rtlefuse->epromtype = EEPROM_BOOT_EFUSE;
	}
	if (tmp_u1b & BIT(5)) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "Autoload OK\n");
		rtlefuse->autoload_failflag = false;
		_rtl8723e_read_adapter_info(hw, false);
	} else {
		rtlefuse->autoload_failflag = true;
		_rtl8723e_read_adapter_info(hw, false);
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG, "Autoload ERR!!\n");
	}
	_rtl8723e_hal_customized_behavior(hw);
}
