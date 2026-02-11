DChannel_proc_rcv(struct IsdnCardState *cs)
{
	struct sk_buff *skb, *nskb;
	struct PStack *stptr = cs->stlist;
	int found, tei, sapi;

	if (stptr)
		if (test_bit(FLG_L1_ACTTIMER, &stptr->l1.Flags))
			FsmEvent(&stptr->l1.l1m, EV_TIMER_ACT, NULL);
	while ((skb = skb_dequeue(&cs->rq))) {
#ifdef L2FRAME_DEBUG
		if (cs->debug & L1_DEB_LAPD)
			Logl2Frame(cs, skb, "PH_DATA", 1);
#endif
		stptr = cs->stlist;
		if (skb->len < 3) {
			debugl1(cs, "D-channel frame too short(%d)", skb->len);
			dev_kfree_skb(skb);
			return;
		}
		if ((skb->data[0] & 1) || !(skb->data[1] & 1)) {
			debugl1(cs, "D-channel frame wrong EA0/EA1");
			dev_kfree_skb(skb);
			return;
		}
		sapi = skb->data[0] >> 2;
		tei = skb->data[1] >> 1;
		if (cs->debug & DEB_DLOG_HEX)
			LogFrame(cs, skb->data, skb->len);
		if (cs->debug & DEB_DLOG_VERBOSE)
			dlogframe(cs, skb, 1);
		if (tei == GROUP_TEI) {
			if (sapi == CTRL_SAPI) {
				while (stptr != NULL) {
					if ((nskb = skb_clone(skb, GFP_ATOMIC)))
						stptr->l1.l1l2(stptr, PH_DATA | INDICATION, nskb);
					else
						printk(KERN_WARNING "HiSax: isdn broadcast buffer shortage\n");
					stptr = stptr->next;
				}
			} else if (sapi == TEI_SAPI) {
				while (stptr != NULL) {
					if ((nskb = skb_clone(skb, GFP_ATOMIC)))
						stptr->l1.l1tei(stptr, PH_DATA | INDICATION, nskb);
					else
						printk(KERN_WARNING "HiSax: tei broadcast buffer shortage\n");
					stptr = stptr->next;
				}
			}
			dev_kfree_skb(skb);
		} else if (sapi == CTRL_SAPI) {
			found = 0;
			while (stptr != NULL)
				if (tei == stptr->l2.tei) {
					stptr->l1.l1l2(stptr, PH_DATA | INDICATION, skb);
					found = !0;
					break;
				} else
					stptr = stptr->next;
			if (!found)
				dev_kfree_skb(skb);
		} else
			dev_kfree_skb(skb);
	}
}
