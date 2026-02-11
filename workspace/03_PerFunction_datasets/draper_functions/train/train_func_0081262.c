allocate_rx_buffer(struct net_device *dev)
{
	struct uli526x_board_info *db = netdev_priv(dev);
	struct rx_desc *rxptr;
	struct sk_buff *skb;

	rxptr = db->rx_insert_ptr;

	while(db->rx_avail_cnt < RX_DESC_CNT) {
		skb = netdev_alloc_skb(dev, RX_ALLOC_SIZE);
		if (skb == NULL)
			break;
		rxptr->rx_skb_ptr = skb;
		rxptr->rdes2 = cpu_to_le32(pci_map_single(db->pdev,
							  skb_tail_pointer(skb),
							  RX_ALLOC_SIZE,
							  PCI_DMA_FROMDEVICE));
		wmb();
		rxptr->rdes0 = cpu_to_le32(0x80000000);
		rxptr = rxptr->next_rx_desc;
		db->rx_avail_cnt++;
	}

	db->rx_insert_ptr = rxptr;
}
