l2_st7_got_super(struct FsmInst *fi, int event, void *arg)
{
	struct layer2 *l2 = fi->userdata;
	struct sk_buff *skb = arg;
	int PollFlag, rsp, typ = RR;
	unsigned int nr;

	rsp = *skb->data & 0x2;
	if (test_bit(FLG_ORIG, &l2->flag))
		rsp = !rsp;

	skb_pull(skb, l2addrsize(l2));
	if (IsRNR(skb->data, l2)) {
		set_peer_busy(l2);
		typ = RNR;
	} else
		clear_peer_busy(l2);
	if (IsREJ(skb->data, l2))
		typ = REJ;

	if (test_bit(FLG_MOD128, &l2->flag)) {
		PollFlag = (skb->data[1] & 0x1) == 0x1;
		nr = skb->data[1] >> 1;
	} else {
		PollFlag = (skb->data[0] & 0x10);
		nr = (skb->data[0] >> 5) & 0x7;
	}
	dev_kfree_skb(skb);

	if (PollFlag) {
		if (rsp)
			l2mgr(l2, MDL_ERROR_IND, (void *) 'A');
		else
			enquiry_response(l2);
	}
	if (legalnr(l2, nr)) {
		if (typ == REJ) {
			setva(l2, nr);
			invoke_retransmission(l2, nr);
			stop_t200(l2, 10);
			if (mISDN_FsmAddTimer(&l2->t203, l2->T203,
					      EV_L2_T203, NULL, 6))
				l2m_debug(&l2->l2m, "Restart T203 ST7 REJ");
		} else if ((nr == l2->vs) && (typ == RR)) {
			setva(l2, nr);
			stop_t200(l2, 11);
			mISDN_FsmRestartTimer(&l2->t203, l2->T203,
					      EV_L2_T203, NULL, 7);
		} else if ((l2->va != nr) || (typ == RNR)) {
			setva(l2, nr);
			if (typ != RR)
				mISDN_FsmDelTimer(&l2->t203, 9);
			restart_t200(l2, 12);
		}
		if (skb_queue_len(&l2->i_queue) && (typ == RR))
			mISDN_FsmEvent(fi, EV_L2_ACK_PULL, NULL);
	} else
		nrerrorrecovery(fi);
}
