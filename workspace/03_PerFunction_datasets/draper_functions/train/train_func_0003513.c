skge_rx_clean(struct skge_port *skge)
{
	struct skge_hw *hw = skge->hw;
	struct skge_ring *ring = &skge->rx_ring;
	struct skge_element *e;

	e = ring->start;
	do {
		struct skge_rx_desc *rd = e->desc;
		rd->control = 0;
		if (e->skb) {
			pci_unmap_single(hw->pdev,
					 dma_unmap_addr(e, mapaddr),
					 dma_unmap_len(e, maplen),
					 PCI_DMA_FROMDEVICE);
			dev_kfree_skb(e->skb);
			e->skb = NULL;
		}
	} while ((e = e->next) != ring->start);
}
