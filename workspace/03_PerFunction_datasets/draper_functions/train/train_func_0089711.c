rsi_get_connected_channel(struct rsi_hw *adapter)
{
	struct ieee80211_vif *vif = adapter->vifs[0];
	if (vif) {
		struct ieee80211_bss_conf *bss = &vif->bss_conf;
		struct ieee80211_channel *channel = bss->chandef.chan;
		return channel->hw_value;
	}

	return 0;
}
