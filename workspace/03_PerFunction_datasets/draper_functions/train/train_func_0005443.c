p54_update_beacon_tim(struct p54_common *priv, u16 aid, bool set)
{
	struct sk_buff *skb;
	struct p54_tim *tim;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL_OPSET, sizeof(*tim),
			    P54_CONTROL_TYPE_TIM, GFP_ATOMIC);
	if (unlikely(!skb))
		return -ENOMEM;

	tim = (struct p54_tim *) skb_put(skb, sizeof(*tim));
	tim->count = 1;
	tim->entry[0] = cpu_to_le16(set ? (aid | 0x8000) : aid);
	p54_tx(priv, skb);
	return 0;
}
