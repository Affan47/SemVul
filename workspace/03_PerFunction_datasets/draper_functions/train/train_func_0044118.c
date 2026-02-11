free_rxtx_rings(struct netdev_private* np)
{
	int i;

	for (i = 0; i < RX_RING_SIZE; i++) {
		np->rx_ring[i].status = 0;
		if (np->rx_skbuff[i]) {
			pci_unmap_single(np->pci_dev,
						np->rx_addr[i],
						np->rx_skbuff[i]->len,
						PCI_DMA_FROMDEVICE);
			dev_kfree_skb(np->rx_skbuff[i]);
		}
		np->rx_skbuff[i] = NULL;
	}
	for (i = 0; i < TX_RING_SIZE; i++) {
		if (np->tx_skbuff[i]) {
			pci_unmap_single(np->pci_dev,
						np->tx_addr[i],
						np->tx_skbuff[i]->len,
						PCI_DMA_TODEVICE);
			dev_kfree_skb(np->tx_skbuff[i]);
		}
		np->tx_skbuff[i] = NULL;
	}
}
