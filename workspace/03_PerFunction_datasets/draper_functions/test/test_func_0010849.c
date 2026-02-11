tulip_free_ring (struct net_device *dev)
{
	struct tulip_private *tp = netdev_priv(dev);
	int i;


	for (i = 0; i < RX_RING_SIZE; i++) {
		struct sk_buff *skb = tp->rx_buffers[i].skb;
		dma_addr_t mapping = tp->rx_buffers[i].mapping;

		tp->rx_buffers[i].skb = NULL;
		tp->rx_buffers[i].mapping = 0;

		tp->rx_ring[i].status = 0;
		tp->rx_ring[i].length = 0;

		tp->rx_ring[i].buffer1 = cpu_to_le32(0xBADF00D0);
		if (skb) {
			pci_unmap_single(tp->pdev, mapping, PKT_BUF_SZ,
					 PCI_DMA_FROMDEVICE);
			dev_kfree_skb (skb);
		}
	}

	for (i = 0; i < TX_RING_SIZE; i++) {
		struct sk_buff *skb = tp->tx_buffers[i].skb;

		if (skb != NULL) {
			pci_unmap_single(tp->pdev, tp->tx_buffers[i].mapping,
					 skb->len, PCI_DMA_TODEVICE);
			dev_kfree_skb (skb);
		}
		tp->tx_buffers[i].skb = NULL;
		tp->tx_buffers[i].mapping = 0;
	}
}
