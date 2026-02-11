carl9170_get_queued_skb(struct ar9170 *ar, u8 cookie,
					       struct sk_buff_head *queue)
{
	struct sk_buff *skb;

	spin_lock_bh(&queue->lock);
	skb_queue_walk(queue, skb) {
		struct _carl9170_tx_superframe *txc = (void *) skb->data;

		if (txc->s.cookie != cookie)
			continue;

		__skb_unlink(skb, queue);
		spin_unlock_bh(&queue->lock);

		carl9170_release_dev_space(ar, skb);
		return skb;
	}
	spin_unlock_bh(&queue->lock);

	return NULL;
}
