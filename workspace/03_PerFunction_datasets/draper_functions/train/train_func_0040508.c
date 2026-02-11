nfcwilink_skb_alloc(unsigned int len, gfp_t how)
{
	struct sk_buff *skb;

	skb = alloc_skb(len + NFCWILINK_HDR_LEN, how);
	if (skb)
		skb_reserve(skb, NFCWILINK_HDR_LEN);

	return skb;
}
