fcoe_ctlr_flogi_send_locked(struct fcoe_ctlr *fip)
{
	struct sk_buff *skb;
	struct sk_buff *skb_orig;
	struct fc_frame_header *fh;
	int error;

	skb_orig = fip->flogi_req;
	if (!skb_orig)
		return -EINVAL;


	skb = skb_clone(skb_orig, GFP_ATOMIC);
	if (!skb) {
		skb = skb_orig;
		fip->flogi_req = NULL;
	}
	fh = (struct fc_frame_header *)skb->data;
	error = fcoe_ctlr_encaps(fip, fip->lp, FIP_DT_FLOGI, skb,
				 ntoh24(fh->fh_d_id));
	if (error) {
		kfree_skb(skb);
		return error;
	}
	fip->send(fip, skb);
	fip->sel_fcf->flogi_sent = 1;
	return 0;
}
