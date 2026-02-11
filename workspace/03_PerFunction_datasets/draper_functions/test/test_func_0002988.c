rtl88e_dm_antenna_div_init(struct ieee80211_hw *hw)
{
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));

	if (rtlefuse->antenna_div_type == CGCS_RX_HW_ANTDIV)
		rtl88e_dm_rx_hw_antena_div_init(hw);
	else if (rtlefuse->antenna_div_type == CG_TRX_HW_ANTDIV)
		rtl88e_dm_trx_hw_antenna_div_init(hw);
	else if (rtlefuse->antenna_div_type == CG_TRX_SMART_ANTDIV)
		rtl88e_dm_fast_training_init(hw);

}
