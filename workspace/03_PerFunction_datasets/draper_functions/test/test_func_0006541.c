refill_rx (struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	int entry;
	int cnt = 0;


	for (;(np->cur_rx - np->dirty_rx + RX_RING_SIZE) % RX_RING_SIZE > 0;
		np->dirty_rx = (np->dirty_rx + 1) % RX_RING_SIZE) {
		struct sk_buff *skb;
		entry = np->dirty_rx % RX_RING_SIZE;
		if (np->rx_skbuff[entry] == NULL) {
			skb = netdev_alloc_skb(dev, np->rx_buf_sz + 2);
			np->rx_skbuff[entry] = skb;
			if (skb == NULL)
				break;
			skb_reserve(skb, 2);
			np->rx_ring[entry].frag[0].addr = cpu_to_le32(
				dma_map_single(&np->pci_dev->dev, skb->data,
					np->rx_buf_sz, DMA_FROM_DEVICE));
			if (dma_mapping_error(&np->pci_dev->dev,
				    np->rx_ring[entry].frag[0].addr)) {
			    dev_kfree_skb_irq(skb);
			    np->rx_skbuff[entry] = NULL;
			    break;
			}
		}

		np->rx_ring[entry].frag[0].length =
			cpu_to_le32(np->rx_buf_sz | LastFrag);
		np->rx_ring[entry].status = 0;
		cnt++;
	}
}
