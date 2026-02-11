rtl8821ae_dm_false_alarm_counter_statistics(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct false_alarm_statistics *falsealm_cnt = &rtlpriv->falsealm_cnt;
	u32 cck_enable = 0;


	falsealm_cnt->cnt_ofdm_fail =
		rtl_get_bbreg(hw, ODM_REG_OFDM_FA_11AC, BMASKLWORD);
	falsealm_cnt->cnt_cck_fail =
		rtl_get_bbreg(hw, ODM_REG_CCK_FA_11AC, BMASKLWORD);

	cck_enable =  rtl_get_bbreg(hw, ODM_REG_BB_RX_PATH_11AC, BIT(28));
	if (cck_enable)
		falsealm_cnt->cnt_all = falsealm_cnt->cnt_ofdm_fail +
					falsealm_cnt->cnt_cck_fail;
	else
		falsealm_cnt->cnt_all = falsealm_cnt->cnt_ofdm_fail;


	rtl_set_bbreg(hw, ODM_REG_OFDM_FA_RST_11AC, BIT(17), 1);
	rtl_set_bbreg(hw, ODM_REG_OFDM_FA_RST_11AC, BIT(17), 0);

	rtl_set_bbreg(hw, ODM_REG_CCK_FA_RST_11AC, BIT(15), 0);
	rtl_set_bbreg(hw, ODM_REG_CCK_FA_RST_11AC, BIT(15), 1);

	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "Cnt_Cck_fail=%d\n",
		 falsealm_cnt->cnt_cck_fail);
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "cnt_ofdm_fail=%d\n",
		 falsealm_cnt->cnt_ofdm_fail);
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "Total False Alarm=%d\n",
		 falsealm_cnt->cnt_all);
}
