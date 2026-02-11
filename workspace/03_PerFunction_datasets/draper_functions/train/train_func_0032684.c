ipw_queue_tx_init(struct ipw_priv *priv,
			     struct clx2_tx_queue *q,
			     int count, u32 read, u32 write, u32 base, u32 size)
{
	struct pci_dev *dev = priv->pci_dev;

	q->txb = kmalloc(sizeof(q->txb[0]) * count, GFP_KERNEL);
	if (!q->txb) {
		IPW_ERROR("vmalloc for auxiliary BD structures failed\n");
		return -ENOMEM;
	}

	q->bd =
	    pci_alloc_consistent(dev, sizeof(q->bd[0]) * count, &q->q.dma_addr);
	if (!q->bd) {
		IPW_ERROR("pci_alloc_consistent(%zd) failed\n",
			  sizeof(q->bd[0]) * count);
		kfree(q->txb);
		q->txb = NULL;
		return -ENOMEM;
	}

	ipw_queue_init(priv, &q->q, count, read, write, base, size);
	return 0;
}
