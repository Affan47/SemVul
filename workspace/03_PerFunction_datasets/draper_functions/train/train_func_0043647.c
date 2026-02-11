mwl8k_get_survey(struct ieee80211_hw *hw, int idx,
				struct survey_info *survey)
{
	struct mwl8k_priv *priv = hw->priv;
	struct ieee80211_conf *conf = &hw->conf;
	struct ieee80211_supported_band *sband;

	if (priv->ap_fw) {
		sband = hw->wiphy->bands[IEEE80211_BAND_2GHZ];

		if (sband && idx >= sband->n_channels) {
			idx -= sband->n_channels;
			sband = NULL;
		}

		if (!sband)
			sband = hw->wiphy->bands[IEEE80211_BAND_5GHZ];

		if (!sband || idx >= sband->n_channels)
			return -ENOENT;

		memcpy(survey, &priv->survey[idx], sizeof(*survey));
		survey->channel = &sband->channels[idx];

		return 0;
	}

	if (idx != 0)
		return -ENOENT;

	survey->channel = conf->chandef.chan;
	survey->filled = SURVEY_INFO_NOISE_DBM;
	survey->noise = priv->noise;

	return 0;
}
