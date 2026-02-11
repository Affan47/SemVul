rtl8821ae_dm_watchdog(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool fw_current_inpsmode = false;
	bool fw_ps_awake = true;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
				      (u8 *)(&fw_current_inpsmode));

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FWLPS_RF_ON,
				      (u8 *)(&fw_ps_awake));

	if (ppsc->p2p_ps_info.p2p_ps_mode)
		fw_ps_awake = false;

	if ((ppsc->rfpwr_state == ERFON) &&
	    ((!fw_current_inpsmode) && fw_ps_awake) &&
	    (!ppsc->rfchange_inprogress)) {
		rtl8821ae_dm_common_info_self_update(hw);
		rtl8821ae_dm_false_alarm_counter_statistics(hw);
		rtl8821ae_dm_check_rssi_monitor(hw);
		rtl8821ae_dm_dig(hw);
		rtl8821ae_dm_cck_packet_detection_thresh(hw);
		rtl8821ae_dm_refresh_rate_adaptive_mask(hw);
		rtl8821ae_dm_refresh_basic_rate_mask(hw);
		rtl8821ae_dm_check_edca_turbo(hw);
		rtl8821ae_dm_dynamic_atc_switch(hw);
		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			rtl8812ae_dm_check_txpower_tracking_thermalmeter(hw);
		else
			rtl8821ae_dm_check_txpower_tracking_thermalmeter(hw);
		rtl8821ae_dm_iq_calibrate(hw);
	}

	rtlpriv->dm.dbginfo.num_qry_beacon_pkt = 0;
	RT_TRACE(rtlpriv, COMP_DIG, DBG_DMESG, "\n");
}
