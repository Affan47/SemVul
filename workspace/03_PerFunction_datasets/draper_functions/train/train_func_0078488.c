p54spi_rx(struct p54s_priv *priv)
{
	struct sk_buff *skb;
	u16 len;
	u16 rx_head[2];
#define READAHEAD_SZ (sizeof(rx_head)-sizeof(u16))

	if (p54spi_wakeup(priv) < 0)
		return -EBUSY;


	p54spi_spi_read(priv, SPI_ADRS_DMA_DATA, rx_head, sizeof(rx_head));
	len = rx_head[0];

	if (len == 0) {
		p54spi_sleep(priv);
		dev_err(&priv->spi->dev, "rx request of zero bytes\n");
		return 0;
	}


	skb = dev_alloc_skb(len + 4);
	if (!skb) {
		p54spi_sleep(priv);
		dev_err(&priv->spi->dev, "could not alloc skb");
		return -ENOMEM;
	}

	if (len <= READAHEAD_SZ) {
		memcpy(skb_put(skb, len), rx_head + 1, len);
	} else {
		memcpy(skb_put(skb, READAHEAD_SZ), rx_head + 1, READAHEAD_SZ);
		p54spi_spi_read(priv, SPI_ADRS_DMA_DATA,
				skb_put(skb, len - READAHEAD_SZ),
				len - READAHEAD_SZ);
	}
	p54spi_sleep(priv);


	skb_put(skb, 4);

	if (p54_rx(priv->hw, skb) == 0)
		dev_kfree_skb(skb);

	return 0;
}
