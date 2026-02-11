rtw_spt_band_alloc(enum ieee80211_band band)
{
	struct ieee80211_supported_band *spt_band = NULL;
	int n_channels, n_bitrates;

	if (band == IEEE80211_BAND_2GHZ) {
		n_channels = RTW_2G_CHANNELS_NUM;
		n_bitrates = RTW_G_RATES_NUM;
	} else if (band == IEEE80211_BAND_5GHZ) {
		n_channels = RTW_5G_CHANNELS_NUM;
		n_bitrates = RTW_A_RATES_NUM;
	} else {
		goto exit;
	}
	spt_band = kzalloc(sizeof(struct ieee80211_supported_band) +
			   sizeof(struct ieee80211_channel) * n_channels +
			   sizeof(struct ieee80211_rate) * n_bitrates,
			   GFP_KERNEL);
	if (!spt_band)
		goto exit;

	spt_band->channels =
		(struct ieee80211_channel *)(((u8 *) spt_band) +
					     sizeof(struct
						    ieee80211_supported_band));
	spt_band->bitrates =
		(struct ieee80211_rate *)(((u8 *) spt_band->channels) +
					  sizeof(struct ieee80211_channel) *
					  n_channels);
	spt_band->band = band;
	spt_band->n_channels = n_channels;
	spt_band->n_bitrates = n_bitrates;

	if (band == IEEE80211_BAND_2GHZ) {
		rtw_2g_channels_init(spt_band->channels);
		rtw_2g_rates_init(spt_band->bitrates);
	} else if (band == IEEE80211_BAND_5GHZ) {
		rtw_5g_channels_init(spt_band->channels);
		rtw_5g_rates_init(spt_band->bitrates);
	}


exit:
	return spt_band;
}
