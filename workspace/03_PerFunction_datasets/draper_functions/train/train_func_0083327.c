receive_new(struct sky2_port *sky2,
				   struct rx_ring_info *re,
				   unsigned int length)
{
	struct sk_buff *skb;
	struct rx_ring_info nre;
	unsigned hdr_space = sky2->rx_data_size;

	nre.skb = sky2_rx_alloc(sky2, GFP_ATOMIC);
	if (unlikely(!nre.skb))
		goto nobuf;

	if (sky2_rx_map_skb(sky2->hw->pdev, &nre, hdr_space))
		goto nomap;

	skb = re->skb;
	sky2_rx_unmap_skb(sky2->hw->pdev, re);
	prefetch(skb->data);
	*re = nre;

	if (skb_shinfo(skb)->nr_frags)
		skb_put_frags(skb, hdr_space, length);
	else
		skb_put(skb, length);
	return skb;

nomap:
	dev_kfree_skb(nre.skb);
nobuf:
	return NULL;
}
