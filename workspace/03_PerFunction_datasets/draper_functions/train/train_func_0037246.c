brcmf_btcoex_timerfunc(ulong data)
{
	struct brcmf_btcoex_info *bt_local = (struct brcmf_btcoex_info *)data;
	brcmf_dbg(TRACE, "enter\n");

	bt_local->timer_on = false;
	schedule_work(&bt_local->work);
}
