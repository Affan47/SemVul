mwifiex_process_mgmt_packet(struct mwifiex_private *priv,
			    struct sk_buff *skb)
{
	struct rxpd *rx_pd;
	u16 pkt_len;
	struct ieee80211_hdr *ieee_hdr;

	if (!skb)
		return -1;

	if (!priv->mgmt_frame_mask ||
	    priv->wdev.iftype == NL80211_IFTYPE_UNSPECIFIED) {
		mwifiex_dbg(priv->adapter, ERROR,
			    "do not receive mgmt frames on uninitialized intf");
		return -1;
	}

	rx_pd = (struct rxpd *)skb->data;

	skb_pull(skb, le16_to_cpu(rx_pd->rx_pkt_offset));
	skb_pull(skb, sizeof(pkt_len));

	pkt_len = le16_to_cpu(rx_pd->rx_pkt_length);

	ieee_hdr = (void *)skb->data;
	if (ieee80211_is_mgmt(ieee_hdr->frame_control)) {
		if (mwifiex_parse_mgmt_packet(priv, (u8 *)ieee_hdr,
					      pkt_len, rx_pd))
			return -1;
	}

	memmove(skb->data + sizeof(struct ieee80211_hdr_3addr),
		skb->data + sizeof(struct ieee80211_hdr),
		pkt_len - sizeof(struct ieee80211_hdr));

	pkt_len -= ETH_ALEN + sizeof(pkt_len);
	rx_pd->rx_pkt_length = cpu_to_le16(pkt_len);

	cfg80211_rx_mgmt(&priv->wdev, priv->roc_cfg.chan.center_freq,
			 CAL_RSSI(rx_pd->snr, rx_pd->nf), skb->data, pkt_len,
			 0);

	return 0;
}
