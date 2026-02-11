rs_update_last_rssi(struct iwl_mvm *mvm,
			 struct iwl_lq_sta *lq_sta,
			 struct ieee80211_rx_status *rx_status)
{
	int i;

	lq_sta->pers.chains = rx_status->chains;
	lq_sta->pers.chain_signal[0] = rx_status->chain_signal[0];
	lq_sta->pers.chain_signal[1] = rx_status->chain_signal[1];
	lq_sta->pers.chain_signal[2] = rx_status->chain_signal[2];
	lq_sta->pers.last_rssi = S8_MIN;

	for (i = 0; i < ARRAY_SIZE(lq_sta->pers.chain_signal); i++) {
		if (!(lq_sta->pers.chains & BIT(i)))
			continue;

		if (lq_sta->pers.chain_signal[i] > lq_sta->pers.last_rssi)
			lq_sta->pers.last_rssi = lq_sta->pers.chain_signal[i];
	}
}
