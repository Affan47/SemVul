ravb_ring_init(struct net_device *ndev, int q)
{
	struct ravb_private *priv = netdev_priv(ndev);
	struct sk_buff *skb;
	int ring_size;
	int i;


	priv->rx_skb[q] = kcalloc(priv->num_rx_ring[q],
				  sizeof(*priv->rx_skb[q]), GFP_KERNEL);
	priv->tx_skb[q] = kcalloc(priv->num_tx_ring[q],
				  sizeof(*priv->tx_skb[q]), GFP_KERNEL);
	if (!priv->rx_skb[q] || !priv->tx_skb[q])
		goto error;

	for (i = 0; i < priv->num_rx_ring[q]; i++) {
		skb = netdev_alloc_skb(ndev, PKT_BUF_SZ + RAVB_ALIGN - 1);
		if (!skb)
			goto error;
		ravb_set_buffer_align(skb);
		priv->rx_skb[q][i] = skb;
	}


	priv->tx_align[q] = kmalloc(DPTR_ALIGN * priv->num_tx_ring[q] +
				    DPTR_ALIGN - 1, GFP_KERNEL);
	if (!priv->tx_align[q])
		goto error;


	ring_size = sizeof(struct ravb_ex_rx_desc) * (priv->num_rx_ring[q] + 1);
	priv->rx_ring[q] = dma_alloc_coherent(ndev->dev.parent, ring_size,
					      &priv->rx_desc_dma[q],
					      GFP_KERNEL);
	if (!priv->rx_ring[q])
		goto error;

	priv->dirty_rx[q] = 0;


	ring_size = sizeof(struct ravb_tx_desc) *
		    (priv->num_tx_ring[q] * NUM_TX_DESC + 1);
	priv->tx_ring[q] = dma_alloc_coherent(ndev->dev.parent, ring_size,
					      &priv->tx_desc_dma[q],
					      GFP_KERNEL);
	if (!priv->tx_ring[q])
		goto error;

	return 0;

error:
	ravb_ring_free(ndev, q);

	return -ENOMEM;
}
