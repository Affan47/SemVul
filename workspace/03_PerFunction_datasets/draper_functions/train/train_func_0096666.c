rtl92c_dm_bt_coexist(struct ieee80211_hw *hw)
{
	struct rtl_pci_priv *rtlpcipriv = rtl_pcipriv(hw);

	bool wifi_connect_change;
	bool bt_state_change;
	bool rssi_state_change;

	if ((rtlpcipriv->bt_coexist.bt_coexistence) &&
	     (rtlpcipriv->bt_coexist.bt_coexist_type == BT_CSR_BC4)) {

		wifi_connect_change = rtl92c_bt_wifi_connect_change(hw);
		bt_state_change = rtl92c_bt_state_change(hw);
		rssi_state_change = rtl92c_bt_rssi_state_change(hw);

		if (wifi_connect_change || bt_state_change || rssi_state_change)
			rtl92c_check_bt_change(hw);
	}
}
