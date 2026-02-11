adm8211_tx_raw(struct ieee80211_hw *dev, struct sk_buff *skb,
			   u16 plcp_signal,
			   size_t hdrlen)
{
	struct adm8211_priv *priv = dev->priv;
	unsigned long flags;
	dma_addr_t mapping;
	unsigned int entry;
	u32 flag;

	mapping = pci_map_single(priv->pdev, skb->data, skb->len,
				 PCI_DMA_TODEVICE);

	spin_lock_irqsave(&priv->lock, flags);

	if (priv->cur_tx - priv->dirty_tx == priv->tx_ring_size / 2)
		flag = TDES1_CONTROL_IC | TDES1_CONTROL_LS | TDES1_CONTROL_FS;
	else
		flag = TDES1_CONTROL_LS | TDES1_CONTROL_FS;

	if (priv->cur_tx - priv->dirty_tx == priv->tx_ring_size - 2)
		ieee80211_stop_queue(dev, 0);

	entry = priv->cur_tx % priv->tx_ring_size;

	priv->tx_buffers[entry].skb = skb;
	priv->tx_buffers[entry].mapping = mapping;
	priv->tx_buffers[entry].hdrlen = hdrlen;
	priv->tx_ring[entry].buffer1 = cpu_to_le32(mapping);

	if (entry == priv->tx_ring_size - 1)
		flag |= TDES1_CONTROL_TER;
	priv->tx_ring[entry].length = cpu_to_le32(flag | skb->len);


	flag = TDES0_CONTROL_OWN | (plcp_signal << 20) | 8 ;
	priv->tx_ring[entry].status = cpu_to_le32(flag);

	priv->cur_tx++;

	spin_unlock_irqrestore(&priv->lock, flags);


	ADM8211_CSR_WRITE(TDR, 0);
}
