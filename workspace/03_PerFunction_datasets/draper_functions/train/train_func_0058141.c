rtl818x_free_tx_ring(struct net80211_device *dev)
{
	struct rtl818x_priv *priv = dev->priv;
	int i;

	for (i = 0; i < RTL818X_TX_RING_SIZE; i++) {
		if (priv->tx_buf[i])
			net80211_tx_complete(dev, priv->tx_buf[i], 0, ECANCELED);
		priv->tx_buf[i] = NULL;
	}

	free_dma(priv->tx_ring, sizeof(*priv->tx_ring) * RTL818X_TX_RING_SIZE);
	priv->tx_ring = NULL;
}
