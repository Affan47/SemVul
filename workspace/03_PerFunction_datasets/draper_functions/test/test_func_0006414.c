wcn36xx_smd_set_bss_nw_type(struct wcn36xx *wcn,
		struct ieee80211_sta *sta,
		struct wcn36xx_hal_config_bss_params *bss_params)
{
	if (IEEE80211_BAND_5GHZ == WCN36XX_BAND(wcn))
		bss_params->nw_type = WCN36XX_HAL_11A_NW_TYPE;
	else if (sta && sta->ht_cap.ht_supported)
		bss_params->nw_type = WCN36XX_HAL_11N_NW_TYPE;
	else if (sta && (sta->supp_rates[IEEE80211_BAND_2GHZ] & 0x7f))
		bss_params->nw_type = WCN36XX_HAL_11G_NW_TYPE;
	else
		bss_params->nw_type = WCN36XX_HAL_11B_NW_TYPE;
}
