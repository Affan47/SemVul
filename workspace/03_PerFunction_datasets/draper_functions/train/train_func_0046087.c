send_disconnect_ind(struct bc_state *bcs,
				struct gigaset_capi_appl *ap, u16 reason)
{
	struct cardstate *cs = bcs->cs;
	struct gigaset_capi_ctr *iif = cs->iif;
	struct sk_buff *skb;

	if (bcs->apconnstate == APCONN_NONE)
		return;

	capi_cmsg_header(&iif->hcmsg, ap->id, CAPI_DISCONNECT, CAPI_IND,
			 ap->nextMessageNumber++,
			 iif->ctr.cnr | ((bcs->channel + 1) << 8));
	iif->hcmsg.Reason = reason;
	skb = alloc_skb(CAPI_DISCONNECT_IND_LEN, GFP_ATOMIC);
	if (!skb) {
		dev_err(cs->dev, "%s: out of memory\n", __func__);
		return;
	}
	if (capi_cmsg2message(&iif->hcmsg,
			      __skb_put(skb, CAPI_DISCONNECT_IND_LEN))) {
		dev_err(cs->dev, "%s: message parser failure\n", __func__);
		dev_kfree_skb_any(skb);
		return;
	}
	dump_cmsg(DEBUG_CMD, __func__, &iif->hcmsg);
	capi_ctr_handle_message(&iif->ctr, ap->id, skb);
}
