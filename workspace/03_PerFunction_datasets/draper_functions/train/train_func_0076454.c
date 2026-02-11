ex_btc8723b2ant_halt_notify(struct btc_coexist *btcoexist)
{
	BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, "[BTCoex], Halt notify\n");

	btc8723b2ant_wifioff_hwcfg(btcoexist);
	btc8723b2ant_ignore_wlan_act(btcoexist, FORCE_EXEC, true);
	ex_btc8723b2ant_media_status_notify(btcoexist, BTC_MEDIA_DISCONNECT);
}
