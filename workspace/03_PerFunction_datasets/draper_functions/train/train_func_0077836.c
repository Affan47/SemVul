brcmf_fws_txs_process(struct brcmf_fws_info *fws, u8 flags, u32 hslot,
		      u32 genbit, u16 seq)
{
	u32 fifo;
	int ret;
	bool remove_from_hanger = true;
	struct sk_buff *skb;
	struct brcmf_skbuff_cb *skcb;
	struct brcmf_fws_mac_descriptor *entry = NULL;
	struct brcmf_if *ifp;

	brcmf_dbg(DATA, "flags %d\n", flags);

	if (flags == BRCMF_FWS_TXSTATUS_DISCARD)
		fws->stats.txs_discard++;
	else if (flags == BRCMF_FWS_TXSTATUS_CORE_SUPPRESS) {
		fws->stats.txs_supp_core++;
		remove_from_hanger = false;
	} else if (flags == BRCMF_FWS_TXSTATUS_FW_PS_SUPPRESS) {
		fws->stats.txs_supp_ps++;
		remove_from_hanger = false;
	} else if (flags == BRCMF_FWS_TXSTATUS_FW_TOSSED)
		fws->stats.txs_tossed++;
	else if (flags == BRCMF_FWS_TXSTATUS_HOST_TOSSED)
		fws->stats.txs_host_tossed++;
	else
		brcmf_err("unexpected txstatus\n");

	ret = brcmf_fws_hanger_poppkt(&fws->hanger, hslot, &skb,
				      remove_from_hanger);
	if (ret != 0) {
		brcmf_err("no packet in hanger slot: hslot=%d\n", hslot);
		return ret;
	}

	skcb = brcmf_skbcb(skb);
	entry = skcb->mac;
	if (WARN_ON(!entry)) {
		brcmu_pkt_buf_free_skb(skb);
		return -EINVAL;
	}
	entry->transit_count--;
	if (entry->suppressed && entry->suppr_transit_count)
		entry->suppr_transit_count--;

	brcmf_dbg(DATA, "%s flags %d htod %X seq %X\n", entry->name, flags,
		  skcb->htod, seq);


	fifo = brcmf_skb_htod_tag_get_field(skb, FIFO);
	if ((fws->fcmode == BRCMF_FWS_FCMODE_IMPLIED_CREDIT) ||
	    (brcmf_skb_if_flags_get_field(skb, REQ_CREDIT)) ||
	    (flags == BRCMF_FWS_TXSTATUS_HOST_TOSSED)) {
		brcmf_fws_return_credits(fws, fifo, 1);
		brcmf_fws_schedule_deq(fws);
	}
	brcmf_fws_macdesc_return_req_credit(skb);

	ret = brcmf_proto_hdrpull(fws->drvr, false, skb, &ifp);
	if (ret) {
		brcmu_pkt_buf_free_skb(skb);
		return -EINVAL;
	}
	if (!remove_from_hanger)
		ret = brcmf_fws_txstatus_suppressed(fws, fifo, skb,
						    genbit, seq);
	if (remove_from_hanger || ret)
		brcmf_txfinalize(ifp, skb, true);

	return 0;
}
