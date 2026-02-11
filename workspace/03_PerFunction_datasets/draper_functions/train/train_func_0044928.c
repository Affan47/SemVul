ath10k_mac_has_radar_iter(struct ieee80211_hw *hw,
				      struct ieee80211_chanctx_conf *conf,
				      void *data)
{
	bool *ret = data;

	if (!*ret && conf->radar_enabled)
		*ret = true;
}
