skbfree(struct sk_buff *skb)
{
	enum { Sms = 250, Tms = 30 * 1000};
	int i = Tms / Sms;

	if (skb == NULL)
		return;
	while (atomic_read(&skb_shinfo(skb)->dataref) != 1 && i-- > 0)
		msleep(Sms);
	if (i < 0) {
		printk(KERN_ERR
			"aoe: %s holds ref: %s\n",
			skb->dev ? skb->dev->name : "netif",
			"cannot free skb -- memory leaked.");
		return;
	}
	skb->truesize -= skb->data_len;
	skb_shinfo(skb)->nr_frags = skb->data_len = 0;
	skb_trim(skb, 0);
	dev_kfree_skb(skb);
}
