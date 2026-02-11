rtl92s_phy_scan_operation_backup(struct ieee80211_hw *hw,
				      u8 operation)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	if (!is_hal_stop(rtlhal)) {
		switch (operation) {
		case SCAN_OPT_BACKUP:
			rtl92s_phy_set_fw_cmd(hw, FW_CMD_PAUSE_DM_BY_SCAN);
			break;
		case SCAN_OPT_RESTORE:
			rtl92s_phy_set_fw_cmd(hw, FW_CMD_RESUME_DM_BY_SCAN);
			break;
		default:
			RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
				 "Unknown operation\n");
			break;
		}
	}
}
