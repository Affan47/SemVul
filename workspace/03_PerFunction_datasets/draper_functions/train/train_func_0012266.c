rtl92d_dm_rxgain_tracking_thermalmeter(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 index_mapping[RX_INDEX_MAPPING_NUM] = {
		0x0f, 0x0f, 0x0d, 0x0c, 0x0b,
		0x0a, 0x09, 0x08, 0x07, 0x06,
		0x05, 0x04, 0x04, 0x03, 0x02
	};
	int i;
	u32 u4tmp;

	u4tmp = (index_mapping[(rtlpriv->efuse.eeprom_thermalmeter -
				rtlpriv->dm.thermalvalue_rxgain)]) << 12;
	RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		 "===> Rx Gain %x\n", u4tmp);
	for (i = RF90_PATH_A; i < rtlpriv->phy.num_total_rfpath; i++)
		rtl_set_rfreg(hw, i, 0x3C, RFREG_OFFSET_MASK,
			      (rtlpriv->phy.reg_rf3c[i] & (~(0xF000))) | u4tmp);
}
