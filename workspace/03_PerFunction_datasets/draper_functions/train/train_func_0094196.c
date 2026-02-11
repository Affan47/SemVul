mt7601u_tx_skb_remove_dma_overhead(struct sk_buff *skb,
					       struct ieee80211_tx_info *info)
{
	int pkt_len = (unsigned long)info->status.status_driver_data[0];

	skb_pull(skb, sizeof(struct mt76_txwi) + 4);
	if (ieee80211_get_hdrlen_from_skb(skb) % 4)
		mt76_remove_hdr_pad(skb);

	skb_trim(skb, pkt_len);
}
