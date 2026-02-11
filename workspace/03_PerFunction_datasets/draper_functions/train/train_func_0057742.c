xgene_enet_create_desc_ring(
			struct net_device *ndev, u32 ring_num,
			enum xgene_enet_ring_cfgsize cfgsize, u32 ring_id)
{
	struct xgene_enet_pdata *pdata = netdev_priv(ndev);
	struct device *dev = ndev_to_dev(ndev);
	struct xgene_enet_desc_ring *ring;
	void *irq_mbox_addr;
	int size;

	size = xgene_enet_get_ring_size(dev, cfgsize);
	if (size < 0)
		return NULL;

	ring = devm_kzalloc(dev, sizeof(struct xgene_enet_desc_ring),
			    GFP_KERNEL);
	if (!ring)
		return NULL;

	ring->ndev = ndev;
	ring->num = ring_num;
	ring->cfgsize = cfgsize;
	ring->id = ring_id;

	ring->desc_addr = dmam_alloc_coherent(dev, size, &ring->dma,
					      GFP_KERNEL | __GFP_ZERO);
	if (!ring->desc_addr) {
		devm_kfree(dev, ring);
		return NULL;
	}
	ring->size = size;

	if (is_irq_mbox_required(pdata, ring)) {
		irq_mbox_addr = dmam_alloc_coherent(dev, INTR_MBOX_SIZE,
						    &ring->irq_mbox_dma,
						    GFP_KERNEL | __GFP_ZERO);
		if (!irq_mbox_addr) {
			dmam_free_coherent(dev, size, ring->desc_addr,
					   ring->dma);
			devm_kfree(dev, ring);
			return NULL;
		}
		ring->irq_mbox_addr = irq_mbox_addr;
	}

	ring->cmd_base = xgene_enet_ring_cmd_base(pdata, ring);
	ring->cmd = ring->cmd_base + INC_DEC_CMD_ADDR;
	ring = pdata->ring_ops->setup(ring);
	netdev_dbg(ndev, "ring info: num=%d  size=%d  id=%d  slots=%d\n",
		   ring->num, ring->size, ring->id, ring->slots);

	return ring;
}
