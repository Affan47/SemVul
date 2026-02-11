ath9k_htc_check_stop_queues(struct ath9k_htc_priv *priv)
{
	spin_lock_bh(&priv->tx.tx_lock);
	priv->tx.queued_cnt++;
	if ((priv->tx.queued_cnt >= ATH9K_HTC_TX_THRESHOLD) &&
	    !(priv->tx.flags & ATH9K_HTC_OP_TX_QUEUES_STOP)) {
		priv->tx.flags |= ATH9K_HTC_OP_TX_QUEUES_STOP;
		ieee80211_stop_queues(priv->hw);
	}
	spin_unlock_bh(&priv->tx.tx_lock);
}
