rsi_mac80211_sta_add(struct ieee80211_hw *hw,
				struct ieee80211_vif *vif,
				struct ieee80211_sta *sta)
{
	struct rsi_hw *adapter = hw->priv;
	struct rsi_common *common = adapter->priv;

	mutex_lock(&common->mutex);

	rsi_set_min_rate(hw, sta, common);

	if ((sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ||
	    (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40)) {
		common->vif_info[0].sgi = true;
	}

	if (sta->ht_cap.ht_supported)
		ieee80211_start_tx_ba_session(sta, 0, 0);

	mutex_unlock(&common->mutex);

	return 0;
}
