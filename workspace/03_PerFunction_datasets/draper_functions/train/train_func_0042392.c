fm10k_ts_tx_enqueue(struct fm10k_intfc *interface, struct sk_buff *skb)
{
	struct sk_buff_head *list = &interface->ts_tx_skb_queue;
	struct sk_buff *clone;
	unsigned long flags;


	clone = skb_clone_sk(skb);
	if (!clone)
		return;

	FM10K_CB(clone)->ts_tx_timeout = jiffies + FM10K_TS_TX_TIMEOUT;
	spin_lock_irqsave(&list->lock, flags);


	skb = fm10k_ts_tx_skb(interface, FM10K_CB(clone)->fi.w.dglort);
	if (!skb) {
		skb_shinfo(clone)->tx_flags |= SKBTX_IN_PROGRESS;
		__skb_queue_tail(list, clone);
	}

	spin_unlock_irqrestore(&list->lock, flags);


	if (skb)
		dev_kfree_skb(clone);
}
