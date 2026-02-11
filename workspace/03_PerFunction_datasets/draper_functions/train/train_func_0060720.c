skb_pool_get(struct aoedev *d)
{
	struct sk_buff *skb = skb_peek(&d->skbpool);

	if (skb && atomic_read(&skb_shinfo(skb)->dataref) == 1) {
		__skb_unlink(skb, &d->skbpool);
		return skb;
	}
	if (skb_queue_len(&d->skbpool) < NSKBPOOLMAX &&
	    (skb = new_skb(ETH_ZLEN)))
		return skb;

	return NULL;
}
