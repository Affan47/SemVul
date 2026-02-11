exhalbtc_update_min_bt_rssi(char bt_rssi)
{
	struct btc_coexist *btcoexist = &gl_bt_coexist;

	if (!halbtc_is_bt_coexist_available(btcoexist))
		return;

	btcoexist->stack_info.min_bt_rssi = bt_rssi;
}
