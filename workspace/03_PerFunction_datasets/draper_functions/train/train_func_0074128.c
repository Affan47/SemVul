stmmac_rx_refill(struct stmmac_priv *priv)
{
	unsigned int rxsize = priv->dma_rx_size;
	int bfsize = priv->dma_buf_sz;

	for (; priv->cur_rx - priv->dirty_rx > 0; priv->dirty_rx++) {
		unsigned int entry = priv->dirty_rx % rxsize;
		struct dma_desc *p;

		if (priv->extend_desc)
			p = (struct dma_desc *)(priv->dma_erx + entry);
		else
			p = priv->dma_rx + entry;

		if (likely(priv->rx_skbuff[entry] == NULL)) {
			struct sk_buff *skb;

			skb = netdev_alloc_skb_ip_align(priv->dev, bfsize);

			if (unlikely(skb == NULL))
				break;

			priv->rx_skbuff[entry] = skb;
			priv->rx_skbuff_dma[entry] =
			    dma_map_single(priv->device, skb->data, bfsize,
					   DMA_FROM_DEVICE);
			if (dma_mapping_error(priv->device,
					      priv->rx_skbuff_dma[entry])) {
				dev_err(priv->device, "Rx dma map failed\n");
				dev_kfree_skb(skb);
				break;
			}
			p->des2 = priv->rx_skbuff_dma[entry];

			priv->hw->mode->refill_desc3(priv, p);

			if (netif_msg_rx_status(priv))
				pr_debug("\trefill entry #%d\n", entry);
		}
		wmb();
		priv->hw->desc->set_rx_owner(p);
		wmb();
	}
}
