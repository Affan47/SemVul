ec_bhf_process_rx(struct ec_bhf_priv *priv)
{
	struct rx_desc *desc = &priv->rx_descs[priv->rx_dnext];

	while (ec_bhf_pkt_received(desc)) {
		int pkt_size = (le16_to_cpu(desc->header.len) &
			       RXHDR_LEN_MASK) - sizeof(struct rx_header) - 4;
		u8 *data = desc->data;
		struct sk_buff *skb;

		skb = netdev_alloc_skb_ip_align(priv->net_dev, pkt_size);
		if (skb) {
			memcpy(skb_put(skb, pkt_size), data, pkt_size);
			skb->protocol = eth_type_trans(skb, priv->net_dev);
			priv->stat_rx_bytes += pkt_size;

			netif_rx(skb);
		} else {
			dev_err_ratelimited(PRIV_TO_DEV(priv),
					    "Couldn't allocate a skb_buff for a packet of size %u\n",
					    pkt_size);
		}

		desc->header.recv = 0;

		ec_bhf_add_rx_desc(priv, desc);

		priv->rx_dnext = (priv->rx_dnext + 1) % priv->rx_dcount;
		desc = &priv->rx_descs[priv->rx_dnext];
	}
}
