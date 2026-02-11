rtl92c_phy_config_rf_with_headerfile(struct ieee80211_hw *hw,
					  enum radio_path rfpath)
{

	int i;
	u32 *radioa_array_table;
	u32 *radiob_array_table;
	u16 radioa_arraylen, radiob_arraylen;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	if (IS_92C_SERIAL(rtlhal->version)) {
		radioa_arraylen = RADIOA_2TARRAYLENGTH;
		radioa_array_table = RTL8192CERADIOA_2TARRAY;
		radiob_arraylen = RADIOB_2TARRAYLENGTH;
		radiob_array_table = RTL8192CE_RADIOB_2TARRAY;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "Radio_A:RTL8192CERADIOA_2TARRAY\n");
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "Radio_B:RTL8192CE_RADIOB_2TARRAY\n");
	} else {
		radioa_arraylen = RADIOA_1TARRAYLENGTH;
		radioa_array_table = RTL8192CE_RADIOA_1TARRAY;
		radiob_arraylen = RADIOB_1TARRAYLENGTH;
		radiob_array_table = RTL8192CE_RADIOB_1TARRAY;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "Radio_A:RTL8192CE_RADIOA_1TARRAY\n");
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "Radio_B:RTL8192CE_RADIOB_1TARRAY\n");
	}
	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE, "Radio No %x\n", rfpath);
	switch (rfpath) {
	case RF90_PATH_A:
		for (i = 0; i < radioa_arraylen; i = i + 2) {
			rtl_rfreg_delay(hw, rfpath, radioa_array_table[i],
					RFREG_OFFSET_MASK,
					radioa_array_table[i + 1]);
		}
		break;
	case RF90_PATH_B:
		for (i = 0; i < radiob_arraylen; i = i + 2) {
			rtl_rfreg_delay(hw, rfpath, radiob_array_table[i],
					RFREG_OFFSET_MASK,
					radiob_array_table[i + 1]);
		}
		break;
	case RF90_PATH_C:
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
			 "switch case not processed\n");
		break;
	case RF90_PATH_D:
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
			 "switch case not processed\n");
		break;
	default:
		break;
	}
	return true;
}
