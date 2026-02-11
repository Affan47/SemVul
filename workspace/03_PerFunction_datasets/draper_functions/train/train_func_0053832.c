rsi_indicate_tx_status(struct rsi_hw *adapter,
			    struct sk_buff *skb,
			    int status)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	memset(info->driver_data, 0, IEEE80211_TX_INFO_DRIVER_DATA_SIZE);

	if (!status)
		info->flags |= IEEE80211_TX_STAT_ACK;

	ieee80211_tx_status_irqsafe(adapter->hw, skb);
}
