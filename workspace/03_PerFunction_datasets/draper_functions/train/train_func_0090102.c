wl1271_init_ap_rates(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int i, ret;
	struct conf_tx_rate_class rc;
	u32 supported_rates;

	wl1271_debug(DEBUG_AP, "AP basic rate set: 0x%x",
		     wlvif->basic_rate_set);

	if (wlvif->basic_rate_set == 0)
		return -EINVAL;

	rc.enabled_rates = wlvif->basic_rate_set;
	rc.long_retry_limit = 10;
	rc.short_retry_limit = 10;
	rc.aflags = 0;
	ret = wl1271_acx_ap_rate_policy(wl, &rc, wlvif->ap.mgmt_rate_idx);
	if (ret < 0)
		return ret;


	rc.enabled_rates = wl1271_tx_min_rate_get(wl, wlvif->basic_rate_set);
	rc.short_retry_limit = 10;
	rc.long_retry_limit = 10;
	rc.aflags = 0;
	ret = wl1271_acx_ap_rate_policy(wl, &rc, wlvif->ap.bcast_rate_idx);
	if (ret < 0)
		return ret;


	if (wl->ofdm_only_ap && (wlvif->basic_rate_set & CONF_TX_OFDM_RATES))
		supported_rates = CONF_TX_OFDM_RATES;
	else
		supported_rates = CONF_TX_ENABLED_RATES;


	supported_rates |= CONF_TX_MCS_RATES;


	supported_rates |= wlcore_hw_ap_get_mimo_wide_rate_mask(wl, wlvif);


	for (i = 0; i < wl->conf.tx.ac_conf_count; i++) {
		rc.enabled_rates = supported_rates;
		rc.short_retry_limit = 10;
		rc.long_retry_limit = 10;
		rc.aflags = 0;
		ret = wl1271_acx_ap_rate_policy(wl, &rc,
						wlvif->ap.ucast_rate_idx[i]);
		if (ret < 0)
			return ret;
	}

	return 0;
}
