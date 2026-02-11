wil_connect_timer_fn(ulong x)
{
	struct wil6210_priv *wil = (void *)x;

	wil_dbg_misc(wil, "Connect timeout\n");


	schedule_work(&wil->disconnect_worker);
}
