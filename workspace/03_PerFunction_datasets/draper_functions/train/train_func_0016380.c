ath9k_beacon_add_noa(struct ath_softc *sc, struct ath_vif *avp,
			  struct sk_buff *skb)
{
	static const u8 noa_ie_hdr[] = {
		WLAN_EID_VENDOR_SPECIFIC,
		0,
		0x50, 0x6f, 0x9a,
		0x09,
		0x0c,
		0x00,
		0x00,
	};

	struct ieee80211_p2p_noa_attr *noa;
	int noa_len, noa_desc, i = 0;
	u8 *hdr;

	if (!avp->offchannel_duration && !avp->noa_duration)
		return;

	noa_desc = !!avp->offchannel_duration + !!avp->noa_duration;
	noa_len = 2 + sizeof(struct ieee80211_p2p_noa_desc) * noa_desc;

	hdr = skb_put(skb, sizeof(noa_ie_hdr));
	memcpy(hdr, noa_ie_hdr, sizeof(noa_ie_hdr));
	hdr[1] = sizeof(noa_ie_hdr) + noa_len - 2;
	hdr[7] = noa_len;

	noa = (void *) skb_put(skb, noa_len);
	memset(noa, 0, noa_len);

	noa->index = avp->noa_index;
	noa->oppps_ctwindow = ath9k_get_ctwin(sc, avp);

	if (avp->noa_duration) {
		if (avp->periodic_noa) {
			u32 interval = TU_TO_USEC(sc->cur_chan->beacon.beacon_interval);
			noa->desc[i].count = 255;
			noa->desc[i].interval = cpu_to_le32(interval);
		} else {
			noa->desc[i].count = 1;
		}

		noa->desc[i].start_time = cpu_to_le32(avp->noa_start);
		noa->desc[i].duration = cpu_to_le32(avp->noa_duration);
		i++;
	}

	if (avp->offchannel_duration) {
		noa->desc[i].count = 1;
		noa->desc[i].start_time = cpu_to_le32(avp->offchannel_start);
		noa->desc[i].duration = cpu_to_le32(avp->offchannel_duration);
	}
}
