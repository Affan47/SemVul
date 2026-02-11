rtl818x_tx(struct net80211_device *dev, struct io_buffer *iob)
{
	struct rtl818x_priv *priv = dev->priv;
	struct rtl818x_tx_desc *entry;
	u32 tx_flags;
	u16 plcp_len = 0;
	int len = iob_len(iob);

	tx_flags = RTL818X_TX_DESC_FLAG_OWN | RTL818X_TX_DESC_FLAG_FS |
		RTL818X_TX_DESC_FLAG_LS | (priv->hw_rate << 24) | len;

	if (priv->r8185) {
		tx_flags |= RTL818X_TX_DESC_FLAG_DMA |
			    RTL818X_TX_DESC_FLAG_NO_ENC;
	} else {
		unsigned int remainder;

		plcp_len = DIV_ROUND_UP(16 * (len + 4),
					(dev->rates[dev->rate] * 2) / 10);
		remainder = (16 * (len + 4)) %
			    ((dev->rates[dev->rate] * 2) / 10);

		if (remainder > 0 && remainder <= 6)
			plcp_len |= 1 << 15;
	}

	entry = &priv->tx_ring[priv->tx_prod];

	if (dev->phy_flags & NET80211_PHY_USE_PROTECTION) {
		tx_flags |= RTL818X_TX_DESC_FLAG_CTS;
		tx_flags |= priv->hw_rtscts_rate << 19;
		entry->rts_duration = net80211_cts_duration(dev, len);
	} else {
		entry->rts_duration = 0;
	}

	if (entry->flags & RTL818X_TX_DESC_FLAG_OWN) {

		return -EBUSY;
	}

	priv->tx_buf[priv->tx_prod] = iob;
	priv->tx_prod = (priv->tx_prod + 1) % RTL818X_TX_RING_SIZE;

	entry->plcp_len = cpu_to_le16(plcp_len);
	entry->tx_buf = cpu_to_le32(virt_to_bus(iob->data));
	entry->frame_len = cpu_to_le32(len);
	entry->flags2 =  0;
	entry->retry_limit = RTL818X_MAX_RETRIES;
	entry->flags = cpu_to_le32(tx_flags);

	rtl818x_iowrite8(priv, &priv->map->TX_DMA_POLLING, (1 << 5));

	return 0;
}
