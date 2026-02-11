ipw_handle_promiscuous_tx(struct ipw_priv *priv,
				      struct libipw_txb *txb)
{
	struct libipw_rx_stats dummystats;
	struct ieee80211_hdr *hdr;
	u8 n;
	u16 filter = priv->prom_priv->filter;
	int hdr_only = 0;

	if (filter & IPW_PROM_NO_TX)
		return;

	memset(&dummystats, 0, sizeof(dummystats));


	hdr = (void *)txb->fragments[0]->data;
	if (libipw_is_management(le16_to_cpu(hdr->frame_control))) {
		if (filter & IPW_PROM_NO_MGMT)
			return;
		if (filter & IPW_PROM_MGMT_HEADER_ONLY)
			hdr_only = 1;
	} else if (libipw_is_control(le16_to_cpu(hdr->frame_control))) {
		if (filter & IPW_PROM_NO_CTL)
			return;
		if (filter & IPW_PROM_CTL_HEADER_ONLY)
			hdr_only = 1;
	} else if (libipw_is_data(le16_to_cpu(hdr->frame_control))) {
		if (filter & IPW_PROM_NO_DATA)
			return;
		if (filter & IPW_PROM_DATA_HEADER_ONLY)
			hdr_only = 1;
	}

	for(n=0; n<txb->nr_frags; ++n) {
		struct sk_buff *src = txb->fragments[n];
		struct sk_buff *dst;
		struct ieee80211_radiotap_header *rt_hdr;
		int len;

		if (hdr_only) {
			hdr = (void *)src->data;
			len = libipw_get_hdrlen(le16_to_cpu(hdr->frame_control));
		} else
			len = src->len;

		dst = alloc_skb(len + sizeof(*rt_hdr) + sizeof(u16)*2, GFP_ATOMIC);
		if (!dst)
			continue;

		rt_hdr = (void *)skb_put(dst, sizeof(*rt_hdr));

		rt_hdr->it_version = PKTHDR_RADIOTAP_VERSION;
		rt_hdr->it_pad = 0;
		rt_hdr->it_present = 0;
		rt_hdr->it_present |=  cpu_to_le32(1 << IEEE80211_RADIOTAP_CHANNEL);

		*(__le16*)skb_put(dst, sizeof(u16)) = cpu_to_le16(
			ieee80211chan2mhz(priv->channel));
		if (priv->channel > 14)
			*(__le16*)skb_put(dst, sizeof(u16)) =
				cpu_to_le16(IEEE80211_CHAN_OFDM |
					     IEEE80211_CHAN_5GHZ);
		else if (priv->ieee->mode == IEEE_B)
			*(__le16*)skb_put(dst, sizeof(u16)) =
				cpu_to_le16(IEEE80211_CHAN_CCK |
					     IEEE80211_CHAN_2GHZ);
		else
			*(__le16*)skb_put(dst, sizeof(u16)) =
				cpu_to_le16(IEEE80211_CHAN_OFDM |
				 IEEE80211_CHAN_2GHZ);

		rt_hdr->it_len = cpu_to_le16(dst->len);

		skb_copy_from_linear_data(src, skb_put(dst, len), len);

		if (!libipw_rx(priv->prom_priv->ieee, dst, &dummystats))
			dev_kfree_skb_any(dst);
	}
}
