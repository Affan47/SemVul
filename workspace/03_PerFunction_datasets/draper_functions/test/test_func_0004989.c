skge_xmit_frame(struct net_device *dev, struct io_buffer *iob)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;
	struct skge_element *e;
	struct skge_tx_desc *td;
	u32 control, len;
	u64 map;

	if (skge_tx_avail(&skge->tx_ring) < 1)
		return -EBUSY;

	e = skge->tx_ring.to_use;
	td = e->desc;
	assert(!(td->control & BMU_OWN));
	e->iob = iob;
	len = iob_len(iob);
	map = virt_to_bus(iob->data);

	td->dma_lo = map;
	td->dma_hi = map >> 32;

	control = BMU_CHECK;

	control |= BMU_EOF| BMU_IRQ_EOF;

	wmb();
	td->control = BMU_OWN | BMU_SW | BMU_STF | control | len;
	wmb();

	skge_write8(hw, Q_ADDR(txqaddr[skge->port], Q_CSR), CSR_START);

	DBGIO(PFX "%s: tx queued, slot %td, len %d\n",
	     dev->name, e - skge->tx_ring.start, (unsigned int)len);

	skge->tx_ring.to_use = e->next;
	wmb();

	if (skge_tx_avail(&skge->tx_ring) <= 1) {
		DBG(PFX "%s: transmit queue full\n", dev->name);
	}

	return 0;
}
