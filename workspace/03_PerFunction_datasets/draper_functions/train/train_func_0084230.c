l2down_skb(struct layer2 *l2, struct sk_buff *skb) {
	int ret;

	ret = l2->ch.recv(l2->ch.peer, skb);
	if (ret && (*debug & DEBUG_L2_RECV))
		printk(KERN_DEBUG "l2down_skb: dev %s ret(%d)\n",
		       mISDNDevName4ch(&l2->ch), ret);
	return ret;
}
