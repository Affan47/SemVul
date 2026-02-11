ath10k_mac_tx_lock(struct ath10k *ar, int reason)
{
	lockdep_assert_held(&ar->htt.tx_lock);

	WARN_ON(reason >= ATH10K_TX_PAUSE_MAX);
	ar->tx_paused |= BIT(reason);
	ieee80211_stop_queues(ar->hw);
}
