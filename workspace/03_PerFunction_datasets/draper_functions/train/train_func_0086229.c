send_DLE_ETX(struct BCState *bcs)
{
	u_char dleetx[2] = {DLE, ETX};
	struct sk_buff *skb;

	if ((skb = dev_alloc_skb(2))) {
		memcpy(skb_put(skb, 2), dleetx, 2);
		skb_queue_tail(&bcs->rqueue, skb);
		schedule_event(bcs, B_RCVBUFREADY);
	} else {
		printk(KERN_WARNING "HiSax: skb out of memory\n");
	}
}
