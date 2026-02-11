gem_alloc_skb(struct net_device *dev, int size,
						gfp_t gfp_flags)
{
	struct sk_buff *skb = alloc_skb(size + 64, gfp_flags);

	if (likely(skb)) {
		unsigned long offset = ALIGNED_RX_SKB_ADDR(skb->data);
		skb_reserve(skb, offset);
	}
	return skb;
}
