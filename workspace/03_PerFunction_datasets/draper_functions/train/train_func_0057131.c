wl1251_ps_elp_sleep(struct wl1251 *wl)
{
	unsigned long delay;

	if (wl->station_mode != STATION_ACTIVE_MODE) {
		delay = msecs_to_jiffies(ELP_ENTRY_DELAY);
		ieee80211_queue_delayed_work(wl->hw, &wl->elp_work, delay);
	}
}
