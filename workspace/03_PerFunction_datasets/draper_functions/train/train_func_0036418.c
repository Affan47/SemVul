cc2520_rx(struct cc2520_private *priv)
{
	u8 len = 0, lqi = 0, bytes = 1;
	struct sk_buff *skb;

	cc2520_read_rxfifo(priv, &len, bytes, &lqi);

	if (len < 2 || len > IEEE802154_MTU)
		return -EINVAL;

	skb = dev_alloc_skb(len);
	if (!skb)
		return -ENOMEM;

	if (cc2520_read_rxfifo(priv, skb_put(skb, len), len, &lqi)) {
		dev_dbg(&priv->spi->dev, "frame reception failed\n");
		kfree_skb(skb);
		return -EINVAL;
	}

	skb_trim(skb, skb->len - 2);

	ieee802154_rx_irqsafe(priv->hw, skb, lqi);

	dev_vdbg(&priv->spi->dev, "RXFIFO: %x %x\n", len, lqi);

	return 0;
}
