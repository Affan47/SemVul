wil6210_disconnect(struct wil6210_priv *wil, const u8 *bssid,
			u16 reason_code, bool from_event)
{
	wil_dbg_misc(wil, "%s()\n", __func__);

	del_timer_sync(&wil->connect_timer);
	_wil6210_disconnect(wil, bssid, reason_code, from_event);
}
