rxq_init(struct net_device *dev)
{
	struct pxa168_eth_private *pep = netdev_priv(dev);
	struct rx_desc *p_rx_desc;
	int size = 0, i = 0;
	int rx_desc_num = pep->rx_ring_size;


	pep->rx_skb = kzalloc(sizeof(*pep->rx_skb) * pep->rx_ring_size,
			     GFP_KERNEL);
	if (!pep->rx_skb)
		return -ENOMEM;


	pep->rx_desc_count = 0;
	size = pep->rx_ring_size * sizeof(struct rx_desc);
	pep->rx_desc_area_size = size;
	pep->p_rx_desc_area = dma_zalloc_coherent(pep->dev->dev.parent, size,
						  &pep->rx_desc_dma,
						  GFP_KERNEL);
	if (!pep->p_rx_desc_area)
		goto out;


	p_rx_desc = pep->p_rx_desc_area;
	for (i = 0; i < rx_desc_num; i++) {
		p_rx_desc[i].next_desc_ptr = pep->rx_desc_dma +
		    ((i + 1) % rx_desc_num) * sizeof(struct rx_desc);
	}

	pep->rx_curr_desc_q = 0;
	pep->rx_used_desc_q = 0;
	pep->rx_desc_area_size = rx_desc_num * sizeof(struct rx_desc);
	return 0;
out:
	kfree(pep->rx_skb);
	return -ENOMEM;
}
