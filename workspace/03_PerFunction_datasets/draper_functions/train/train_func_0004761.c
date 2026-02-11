wlcore_scan_sched_scan_results(struct wl1271 *wl)
{
	wl1271_debug(DEBUG_SCAN, "got periodic scan results");

	ieee80211_sched_scan_results(wl->hw);
}
