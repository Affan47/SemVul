rtl8723be_set_fw_pwrmode_cmd(struct ieee80211_hw *hw, u8 mode)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 u1_h2c_set_pwrmode[H2C_PWEMODE_LENGTH] = { 0 };
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u8 rlbm, power_state = 0;
	RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD, "FW LPS mode = %d\n", mode);

	SET_H2CCMD_PWRMODE_PARM_MODE(u1_h2c_set_pwrmode, ((mode) ? 1 : 0));
	rlbm = 0;
	SET_H2CCMD_PWRMODE_PARM_RLBM(u1_h2c_set_pwrmode, rlbm);
	SET_H2CCMD_PWRMODE_PARM_SMART_PS(u1_h2c_set_pwrmode,
					 (rtlpriv->mac80211.p2p) ?
					  ppsc->smart_ps : 1);
	SET_H2CCMD_PWRMODE_PARM_AWAKE_INTERVAL(u1_h2c_set_pwrmode,
					       ppsc->reg_max_lps_awakeintvl);
	SET_H2CCMD_PWRMODE_PARM_ALL_QUEUE_UAPSD(u1_h2c_set_pwrmode, 0);
	if (mode == FW_PS_ACTIVE_MODE)
		power_state |= FW_PWR_STATE_ACTIVE;
	else
		power_state |= FW_PWR_STATE_RF_OFF;
	SET_H2CCMD_PWRMODE_PARM_PWR_STATE(u1_h2c_set_pwrmode, power_state);

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_DMESG,
		      "rtl92c_set_fw_pwrmode(): u1_h2c_set_pwrmode\n",
		      u1_h2c_set_pwrmode, H2C_PWEMODE_LENGTH);
	rtl8723be_fill_h2c_cmd(hw, H2C_8723B_SETPWRMODE, H2C_PWEMODE_LENGTH,
			       u1_h2c_set_pwrmode);
}
