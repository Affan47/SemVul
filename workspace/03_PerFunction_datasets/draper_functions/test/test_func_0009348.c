epic_close(struct net_device *dev)
{
	struct epic_private *ep = netdev_priv(dev);
	struct pci_dev *pdev = ep->pci_dev;
	void __iomem *ioaddr = ep->ioaddr;
	struct sk_buff *skb;
	int i;

	netif_stop_queue(dev);
	napi_disable(&ep->napi);

	if (debug > 1)
		netdev_dbg(dev, "Shutting down ethercard, status was %2.2x.\n",
			   er32(INTSTAT));

	del_timer_sync(&ep->timer);

	epic_disable_int(dev, ep);

	free_irq(pdev->irq, dev);

	epic_pause(dev);


	for (i = 0; i < RX_RING_SIZE; i++) {
		skb = ep->rx_skbuff[i];
		ep->rx_skbuff[i] = NULL;
		ep->rx_ring[i].rxstatus = 0;
		ep->rx_ring[i].buflength = 0;
		if (skb) {
			pci_unmap_single(pdev, ep->rx_ring[i].bufaddr,
					 ep->rx_buf_sz, PCI_DMA_FROMDEVICE);
			dev_kfree_skb(skb);
		}
		ep->rx_ring[i].bufaddr = 0xBADF00D0;
	}
	for (i = 0; i < TX_RING_SIZE; i++) {
		skb = ep->tx_skbuff[i];
		ep->tx_skbuff[i] = NULL;
		if (!skb)
			continue;
		pci_unmap_single(pdev, ep->tx_ring[i].bufaddr, skb->len,
				 PCI_DMA_TODEVICE);
		dev_kfree_skb(skb);
	}


	ew32(GENCTL, 0x0008);

	return 0;
}
