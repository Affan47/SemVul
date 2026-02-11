ath9k_htc_tx_get_packet(struct ath9k_htc_priv *priv,
					       struct __wmi_event_txstatus *txs)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct sk_buff_head *epid_queue;
	struct sk_buff *skb, *tmp;
	unsigned long flags;
	u8 epid = MS(txs->ts_rate, ATH9K_HTC_TXSTAT_EPID);

	epid_queue = get_htc_epid_queue(priv, epid);
	if (!epid_queue)
		return NULL;

	spin_lock_irqsave(&epid_queue->lock, flags);
	skb_queue_walk_safe(epid_queue, skb, tmp) {
		if (check_cookie(priv, skb, txs->cookie, epid)) {
			__skb_unlink(skb, epid_queue);
			spin_unlock_irqrestore(&epid_queue->lock, flags);
			return skb;
		}
	}
	spin_unlock_irqrestore(&epid_queue->lock, flags);

	ath_dbg(common, XMIT, "No matching packet for cookie: %d, epid: %d\n",
		txs->cookie, epid);

	return NULL;
}
