start_tx (struct sk_buff *skb, struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	struct netdev_desc *txdesc;
	unsigned entry;


	entry = np->cur_tx % TX_RING_SIZE;
	np->tx_skbuff[entry] = skb;
	txdesc = &np->tx_ring[entry];

	txdesc->next_desc = 0;
	txdesc->status = cpu_to_le32 ((entry << 2) | DisableAlign);
	txdesc->frag[0].addr = cpu_to_le32(dma_map_single(&np->pci_dev->dev,
				skb->data, skb->len, DMA_TO_DEVICE));
	if (dma_mapping_error(&np->pci_dev->dev,
				txdesc->frag[0].addr))
			goto drop_frame;
	txdesc->frag[0].length = cpu_to_le32 (skb->len | LastFrag);


	np->cur_tx++;
	mb();

	tasklet_schedule(&np->tx_tasklet);


	if (np->cur_tx - np->dirty_tx < TX_QUEUE_LEN - 1 &&
	    !netif_queue_stopped(dev)) {

	} else {
		netif_stop_queue (dev);
	}
	if (netif_msg_tx_queued(np)) {
		printk (KERN_DEBUG
			"%s: Transmit frame #%d queued in slot %d.\n",
			dev->name, np->cur_tx, entry);
	}
	return NETDEV_TX_OK;

drop_frame:
	dev_kfree_skb_any(skb);
	np->tx_skbuff[entry] = NULL;
	dev->stats.tx_dropped++;
	return NETDEV_TX_OK;
}
