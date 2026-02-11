brcmf_fws_hdrpush(struct brcmf_fws_info *fws, struct sk_buff *skb)
{
	struct brcmf_fws_mac_descriptor *entry = brcmf_skbcb(skb)->mac;
	u8 *wlh;
	u16 data_offset = 0;
	u8 fillers;
	__le32 pkttag = cpu_to_le32(brcmf_skbcb(skb)->htod);
	__le16 pktseq = cpu_to_le16(brcmf_skbcb(skb)->htod_seq);

	brcmf_dbg(TRACE, "enter: %s, idx=%d hslot=%d htod %X seq %X\n",
		  entry->name, brcmf_skb_if_flags_get_field(skb, INDEX),
		  (le32_to_cpu(pkttag) >> 8) & 0xffff,
		  brcmf_skbcb(skb)->htod, brcmf_skbcb(skb)->htod_seq);
	if (entry->send_tim_signal)
		data_offset += 2 + BRCMF_FWS_TYPE_PENDING_TRAFFIC_BMP_LEN;
	if (BRCMF_FWS_MODE_GET_REUSESEQ(fws->mode))
		data_offset += BRCMF_FWS_TYPE_SEQ_LEN;

	data_offset += 2 + BRCMF_FWS_TYPE_PKTTAG_LEN;
	fillers = round_up(data_offset, 4) - data_offset;
	data_offset += fillers;

	skb_push(skb, data_offset);
	wlh = skb->data;

	wlh[0] = BRCMF_FWS_TYPE_PKTTAG;
	wlh[1] = BRCMF_FWS_TYPE_PKTTAG_LEN;
	memcpy(&wlh[2], &pkttag, sizeof(pkttag));
	if (BRCMF_FWS_MODE_GET_REUSESEQ(fws->mode)) {
		wlh[1] += BRCMF_FWS_TYPE_SEQ_LEN;
		memcpy(&wlh[2 + BRCMF_FWS_TYPE_PKTTAG_LEN], &pktseq,
		       sizeof(pktseq));
	}
	wlh += wlh[1] + 2;

	if (entry->send_tim_signal) {
		entry->send_tim_signal = 0;
		wlh[0] = BRCMF_FWS_TYPE_PENDING_TRAFFIC_BMP;
		wlh[1] = BRCMF_FWS_TYPE_PENDING_TRAFFIC_BMP_LEN;
		wlh[2] = entry->mac_handle;
		wlh[3] = entry->traffic_pending_bmp;
		brcmf_dbg(TRACE, "adding TIM info: handle %d bmp 0x%X\n",
			  entry->mac_handle, entry->traffic_pending_bmp);
		wlh += BRCMF_FWS_TYPE_PENDING_TRAFFIC_BMP_LEN + 2;
		entry->traffic_lastreported_bmp = entry->traffic_pending_bmp;
	}
	if (fillers)
		memset(wlh, BRCMF_FWS_TYPE_FILLER, fillers);

	return (u8)(data_offset >> 2);
}
