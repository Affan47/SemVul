_rtl8821ae_get_wakeup_reason(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	u8 fw_reason = 0;
	struct timeval ts;

	fw_reason = rtl_read_byte(rtlpriv, REG_MCUTST_WOWLAN);

	RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD, "WOL Read 0x1c7 = %02X\n",
		 fw_reason);

	ppsc->wakeup_reason = 0;

	do_gettimeofday(&ts);
	rtlhal->last_suspend_sec = ts.tv_sec;

	switch (fw_reason) {
	case FW_WOW_V2_PTK_UPDATE_EVENT:
		ppsc->wakeup_reason = WOL_REASON_PTK_UPDATE;
		do_gettimeofday(&ts);
		ppsc->last_wakeup_time = ts.tv_sec*1000 + ts.tv_usec/1000;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's a WOL PTK Key update event!\n");
		break;
	case FW_WOW_V2_GTK_UPDATE_EVENT:
		ppsc->wakeup_reason = WOL_REASON_GTK_UPDATE;
		do_gettimeofday(&ts);
		ppsc->last_wakeup_time = ts.tv_sec*1000 + ts.tv_usec/1000;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's a WOL GTK Key update event!\n");
		break;
	case FW_WOW_V2_DISASSOC_EVENT:
		ppsc->wakeup_reason = WOL_REASON_DISASSOC;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's a disassociation event!\n");
		break;
	case FW_WOW_V2_DEAUTH_EVENT:
		ppsc->wakeup_reason = WOL_REASON_DEAUTH;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's a deauth event!\n");
		break;
	case FW_WOW_V2_FW_DISCONNECT_EVENT:
		ppsc->wakeup_reason = WOL_REASON_AP_LOST;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's a Fw disconnect decision (AP lost) event!\n");
	break;
	case FW_WOW_V2_MAGIC_PKT_EVENT:
		ppsc->wakeup_reason = WOL_REASON_MAGIC_PKT;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's a magic packet event!\n");
		break;
	case FW_WOW_V2_UNICAST_PKT_EVENT:
		ppsc->wakeup_reason = WOL_REASON_UNICAST_PKT;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's an unicast packet event!\n");
		break;
	case FW_WOW_V2_PATTERN_PKT_EVENT:
		ppsc->wakeup_reason = WOL_REASON_PATTERN_PKT;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's a pattern match event!\n");
		break;
	case FW_WOW_V2_RTD3_SSID_MATCH_EVENT:
		ppsc->wakeup_reason = WOL_REASON_RTD3_SSID_MATCH;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's an RTD3 Ssid match event!\n");
		break;
	case FW_WOW_V2_REALWOW_V2_WAKEUPPKT:
		ppsc->wakeup_reason = WOL_REASON_REALWOW_V2_WAKEUPPKT;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's an RealWoW wake packet event!\n");
		break;
	case FW_WOW_V2_REALWOW_V2_ACKLOST:
		ppsc->wakeup_reason = WOL_REASON_REALWOW_V2_ACKLOST;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "It's an RealWoW ack lost event!\n");
		break;
	default:
		RT_TRACE(rtlpriv, COMP_POWER, DBG_DMESG,
			 "WOL Read 0x1c7 = %02X, Unknown reason!\n",
			  fw_reason);
		break;
	}
}
