sirdev_alloc_buffers(struct sir_dev *dev)
{
	dev->tx_buff.truesize = SIRBUF_ALLOCSIZE;
	dev->rx_buff.truesize = IRDA_SKB_MAX_MTU;


	dev->rx_buff.skb = __netdev_alloc_skb(dev->netdev, dev->rx_buff.truesize,
					      GFP_KERNEL);
	if (dev->rx_buff.skb == NULL)
		return -ENOMEM;
	skb_reserve(dev->rx_buff.skb, 1);
	dev->rx_buff.head = dev->rx_buff.skb->data;

	dev->tx_buff.head = kmalloc(dev->tx_buff.truesize, GFP_KERNEL);
	if (dev->tx_buff.head == NULL) {
		kfree_skb(dev->rx_buff.skb);
		dev->rx_buff.skb = NULL;
		dev->rx_buff.head = NULL;
		return -ENOMEM;
	}

	dev->tx_buff.data = dev->tx_buff.head;
	dev->rx_buff.data = dev->rx_buff.head;
	dev->tx_buff.len = 0;
	dev->rx_buff.len = 0;

	dev->rx_buff.in_frame = FALSE;
	dev->rx_buff.state = OUTSIDE_FRAME;
	return 0;
}
