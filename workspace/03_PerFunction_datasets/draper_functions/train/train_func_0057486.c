wcn36xx_smd_set_sta_params(struct wcn36xx *wcn,
		struct ieee80211_vif *vif,
		struct ieee80211_sta *sta,
		struct wcn36xx_hal_config_sta_params *sta_params)
{
	struct wcn36xx_vif *priv_vif = (struct wcn36xx_vif *)vif->drv_priv;
	struct wcn36xx_sta *priv_sta = NULL;
	if (vif->type == NL80211_IFTYPE_ADHOC ||
	    vif->type == NL80211_IFTYPE_AP ||
	    vif->type == NL80211_IFTYPE_MESH_POINT) {
		sta_params->type = 1;
		sta_params->sta_index = 0xFF;
	} else {
		sta_params->type = 0;
		sta_params->sta_index = 1;
	}

	sta_params->listen_interval = WCN36XX_LISTEN_INTERVAL(wcn);


	if (NL80211_IFTYPE_STATION == vif->type)
		memcpy(&sta_params->mac, vif->addr, ETH_ALEN);
	else
		memcpy(&sta_params->bssid, vif->addr, ETH_ALEN);

	sta_params->encrypt_type = priv_vif->encrypt_type;
	sta_params->short_preamble_supported = true;

	sta_params->rifs_mode = 0;
	sta_params->rmf = 0;
	sta_params->action = 0;
	sta_params->uapsd = 0;
	sta_params->mimo_ps = WCN36XX_HAL_HT_MIMO_PS_STATIC;
	sta_params->max_ampdu_duration = 0;
	sta_params->bssid_index = priv_vif->bss_index;
	sta_params->p2p = 0;

	if (sta) {
		priv_sta = (struct wcn36xx_sta *)sta->drv_priv;
		if (NL80211_IFTYPE_STATION == vif->type)
			memcpy(&sta_params->bssid, sta->addr, ETH_ALEN);
		else
			memcpy(&sta_params->mac, sta->addr, ETH_ALEN);
		sta_params->wmm_enabled = sta->wme;
		sta_params->max_sp_len = sta->max_sp;
		sta_params->aid = priv_sta->aid;
		wcn36xx_smd_set_sta_ht_params(sta, sta_params);
		memcpy(&sta_params->supported_rates, &priv_sta->supported_rates,
			sizeof(priv_sta->supported_rates));
	} else {
		wcn36xx_set_default_rates(&sta_params->supported_rates);
		wcn36xx_smd_set_sta_default_ht_params(sta_params);
	}
}
