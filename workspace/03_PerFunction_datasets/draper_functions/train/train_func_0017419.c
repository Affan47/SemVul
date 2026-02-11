llt_ndlc_rcv_queue(struct llt_ndlc *ndlc)
{
	struct sk_buff *skb;
	u8 pcb;
	unsigned long time_sent;

	if (ndlc->rcv_q.qlen)
		pr_debug("rcvQlen=%d\n", ndlc->rcv_q.qlen);

	while ((skb = skb_dequeue(&ndlc->rcv_q)) != NULL) {
		pcb = skb->data[0];
		skb_pull(skb, 1);
		if ((pcb & PCB_TYPE_MASK) == PCB_TYPE_SUPERVISOR) {
			switch (pcb & PCB_SYNC_MASK) {
			case PCB_SYNC_ACK:
				skb = skb_dequeue(&ndlc->ack_pending_q);
				kfree_skb(skb);
				del_timer_sync(&ndlc->t1_timer);
				del_timer_sync(&ndlc->t2_timer);
				ndlc->t2_active = false;
				ndlc->t1_active = false;
				break;
			case PCB_SYNC_NACK:
				llt_ndlc_requeue_data_pending(ndlc);
				llt_ndlc_send_queue(ndlc);

				time_sent = jiffies;
				ndlc->t1_active = true;
				mod_timer(&ndlc->t1_timer, time_sent +
					msecs_to_jiffies(NDLC_TIMER_T1));
				break;
			case PCB_SYNC_WAIT:
				time_sent = jiffies;
				ndlc->t1_active = true;
				mod_timer(&ndlc->t1_timer, time_sent +
					  msecs_to_jiffies(NDLC_TIMER_T1_WAIT));
				break;
			default:
				kfree_skb(skb);
				break;
			}
		} else if ((pcb & PCB_TYPE_MASK) == PCB_TYPE_DATAFRAME) {
			nci_recv_frame(ndlc->ndev, skb);
		} else {
			kfree_skb(skb);
		}
	}
}
