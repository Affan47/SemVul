wl1271_unregister_hw(struct wl1271 *wl)
{
	if (wl->plt)
		wl1271_plt_stop(wl);

	ieee80211_unregister_hw(wl->hw);
	wl->mac80211_registered = false;

}
