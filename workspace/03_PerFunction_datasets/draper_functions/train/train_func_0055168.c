ar5523_get_wlan_mode(struct ar5523 *ar,
				struct ieee80211_bss_conf *bss_conf)
{
	struct ieee80211_supported_band *band;
	int bit;
	struct ieee80211_sta *sta;
	u32 sta_rate_set;

	band = ar->hw->wiphy->bands[ar->hw->conf.chandef.chan->band];
	sta = ieee80211_find_sta(ar->vif, bss_conf->bssid);
	if (!sta) {
		ar5523_info(ar, "STA not found!\n");
		return WLAN_MODE_11b;
	}
	sta_rate_set = sta->supp_rates[ar->hw->conf.chandef.chan->band];

	for (bit = 0; bit < band->n_bitrates; bit++) {
		if (sta_rate_set & 1) {
			int rate = band->bitrates[bit].bitrate;
			switch (rate) {
			case 60:
			case 90:
			case 120:
			case 180:
			case 240:
			case 360:
			case 480:
			case 540:
				return WLAN_MODE_11g;
			}
		}
		sta_rate_set >>= 1;
	}
	return WLAN_MODE_11b;
}
