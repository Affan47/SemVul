wl1271_set_ba_policies(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{

	wlvif->ba_allowed = true;
	wl->ba_rx_session_count = 0;


	if (wlvif->bss_type != BSS_TYPE_AP_BSS &&
	    wlvif->bss_type != BSS_TYPE_STA_BSS) {
		wlvif->ba_support = false;
		return 0;
	}

	wlvif->ba_support = true;


	return wl12xx_acx_set_ba_initiator_policy(wl, wlvif);
}
