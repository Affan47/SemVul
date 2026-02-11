dm9601_tx_fixup(struct usbnet *dev, struct sk_buff *skb,
				       gfp_t flags)
{
	int len, pad;


	len = skb->len + DM_TX_OVERHEAD;


	while ((len & 1) || !(len % dev->maxpacket))
		len++;

	len -= DM_TX_OVERHEAD;
	pad = len - skb->len;

	if (skb_headroom(skb) < DM_TX_OVERHEAD || skb_tailroom(skb) < pad) {
		struct sk_buff *skb2;

		skb2 = skb_copy_expand(skb, DM_TX_OVERHEAD, pad, flags);
		dev_kfree_skb_any(skb);
		skb = skb2;
		if (!skb)
			return NULL;
	}

	__skb_push(skb, DM_TX_OVERHEAD);

	if (pad) {
		memset(skb->data + skb->len, 0, pad);
		__skb_put(skb, pad);
	}

	skb->data[0] = len;
	skb->data[1] = len >> 8;

	return skb;
}
