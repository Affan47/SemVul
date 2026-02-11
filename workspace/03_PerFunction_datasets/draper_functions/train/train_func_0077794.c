wl12xx_init_sta_role(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int ret;

	ret = wl1271_acx_group_address_tbl(wl, wlvif, true, NULL, 0);
	if (ret < 0)
		return ret;


	ret = wl1271_acx_conn_monit_params(wl, wlvif, false);
	if (ret < 0)
		return ret;


	ret = wl1271_init_sta_beacon_filter(wl, wlvif);
	if (ret < 0)
		return ret;


	ret = wl1271_init_beacon_broadcast(wl, wlvif);
	if (ret < 0)
		return ret;


	ret = wl1271_acx_rssi_snr_avg_weights(wl, wlvif);
	if (ret < 0)
		return ret;

	return 0;
}
