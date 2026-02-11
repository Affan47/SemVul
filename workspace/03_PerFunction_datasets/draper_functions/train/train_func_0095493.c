pcnet32_purge_tx_ring(struct net_device *dev)
{
	struct pcnet32_private *lp = netdev_priv(dev);
	int i;

	for (i = 0; i < lp->tx_ring_size; i++) {
		lp->tx_ring[i].status = 0;
		wmb();
		if (lp->tx_skbuff[i]) {
			if (!pci_dma_mapping_error(lp->pci_dev,
						   lp->tx_dma_addr[i]))
				pci_unmap_single(lp->pci_dev,
						 lp->tx_dma_addr[i],
						 lp->tx_skbuff[i]->len,
						 PCI_DMA_TODEVICE);
			dev_kfree_skb_any(lp->tx_skbuff[i]);
		}
		lp->tx_skbuff[i] = NULL;
		lp->tx_dma_addr[i] = 0;
	}
}
