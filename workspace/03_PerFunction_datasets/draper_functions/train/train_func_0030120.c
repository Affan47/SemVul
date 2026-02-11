exhalbtc_mediastatus_notify(struct btc_coexist *btcoexist,
				 enum rt_media_status media_status)
{
	u8 status;

	if (!halbtc_is_bt_coexist_available(btcoexist))
		return;
	btcoexist->statistics.cnt_media_status_notify++;
	if (btcoexist->manual_control)
		return;

	if (RT_MEDIA_CONNECT == media_status)
		status = BTC_MEDIA_CONNECT;
	else
		status = BTC_MEDIA_DISCONNECT;

	halbtc_leave_low_power();

	halbtc_nomal_low_power();
}
