encx24j600_receive_packet(struct encx24j600_priv *priv,
				     struct rsv *rsv)
{
	struct net_device *dev = priv->ndev;
	struct sk_buff *skb = netdev_alloc_skb(dev, rsv->len + NET_IP_ALIGN);
	if (!skb) {
		pr_err_ratelimited("RX: OOM: packet dropped\n");
		dev->stats.rx_dropped++;
		return -ENOMEM;
	}
	skb_reserve(skb, NET_IP_ALIGN);
	encx24j600_raw_read(priv, RRXDATA, skb_put(skb, rsv->len), rsv->len);

	if (netif_msg_pktdata(priv))
		dump_packet("RX", skb->len, skb->data);

	skb->dev = dev;
	skb->protocol = eth_type_trans(skb, dev);
	skb->ip_summed = CHECKSUM_COMPLETE;


	dev->stats.rx_packets++;
	dev->stats.rx_bytes += rsv->len;
	priv->next_packet = rsv->next_packet;

	netif_rx(skb);

	return 0;
}
