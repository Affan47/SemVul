check_packet(struct ath9k_htc_priv *priv, struct sk_buff *skb)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ath9k_htc_tx_ctl *tx_ctl;

	tx_ctl = HTC_SKB_CB(skb);

	if (time_after(jiffies,
		       tx_ctl->timestamp +
		       msecs_to_jiffies(ATH9K_HTC_TX_TIMEOUT_INTERVAL))) {
		ath_dbg(common, XMIT, "Dropping a packet due to TX timeout\n");
		return true;
	}

	return false;
}
