wcn36xx_rx_skb(struct wcn36xx *wcn, struct sk_buff *skb)
{
	struct ieee80211_rx_status status;
	struct ieee80211_hdr *hdr;
	struct wcn36xx_rx_bd *bd;
	u16 fc, sn;


	memset(&status, 0, sizeof(status));

	bd = (struct wcn36xx_rx_bd *)skb->data;
	buff_to_be((u32 *)bd, sizeof(*bd)/sizeof(u32));
	wcn36xx_dbg_dump(WCN36XX_DBG_RX_DUMP,
			 "BD   <<< ", (char *)bd,
			 sizeof(struct wcn36xx_rx_bd));

	skb_put(skb, bd->pdu.mpdu_header_off + bd->pdu.mpdu_len);
	skb_pull(skb, bd->pdu.mpdu_header_off);

	status.mactime = 10;
	status.freq = WCN36XX_CENTER_FREQ(wcn);
	status.band = WCN36XX_BAND(wcn);
	status.signal = -get_rssi0(bd);
	status.antenna = 1;
	status.rate_idx = 1;
	status.flag = 0;
	status.rx_flags = 0;
	status.flag |= RX_FLAG_IV_STRIPPED |
		       RX_FLAG_MMIC_STRIPPED |
		       RX_FLAG_DECRYPTED;

	wcn36xx_dbg(WCN36XX_DBG_RX, "status.flags=%x\n", status.flag);

	memcpy(IEEE80211_SKB_RXCB(skb), &status, sizeof(status));

	hdr = (struct ieee80211_hdr *) skb->data;
	fc = __le16_to_cpu(hdr->frame_control);
	sn = IEEE80211_SEQ_TO_SN(__le16_to_cpu(hdr->seq_ctrl));

	if (ieee80211_is_beacon(hdr->frame_control)) {
		wcn36xx_dbg(WCN36XX_DBG_BEACON, "beacon skb %p len %d fc %04x sn %d\n",
			    skb, skb->len, fc, sn);
		wcn36xx_dbg_dump(WCN36XX_DBG_BEACON_DUMP, "SKB <<< ",
				 (char *)skb->data, skb->len);
	} else {
		wcn36xx_dbg(WCN36XX_DBG_RX, "rx skb %p len %d fc %04x sn %d\n",
			    skb, skb->len, fc, sn);
		wcn36xx_dbg_dump(WCN36XX_DBG_RX_DUMP, "SKB <<< ",
				 (char *)skb->data, skb->len);
	}

	ieee80211_rx_irqsafe(wcn->hw, skb);

	return 0;
}
