ath10k_station_disassoc(struct ath10k *ar,
				   struct ieee80211_vif *vif,
				   struct ieee80211_sta *sta)
{
	struct ath10k_vif *arvif = ath10k_vif_to_arvif(vif);
	int ret = 0;

	lockdep_assert_held(&ar->conf_mutex);

	if (!sta->wme) {
		arvif->num_legacy_stations--;
		ret = ath10k_recalc_rtscts_prot(arvif);
		if (ret) {
			ath10k_warn(ar, "failed to recalculate rts/cts prot for vdev %d: %d\n",
				    arvif->vdev_id, ret);
			return ret;
		}
	}

	ret = ath10k_clear_peer_keys(arvif, sta->addr);
	if (ret) {
		ath10k_warn(ar, "failed to clear all peer wep keys for vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	return ret;
}
