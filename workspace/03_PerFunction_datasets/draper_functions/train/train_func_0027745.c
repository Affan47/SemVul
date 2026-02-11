mt7601u_alloc_rx(struct mt7601u_dev *dev)
{
	int i;

	memset(&dev->rx_q, 0, sizeof(dev->rx_q));
	dev->rx_q.dev = dev;
	dev->rx_q.entries = N_RX_ENTRIES;

	for (i = 0; i < N_RX_ENTRIES; i++) {
		dev->rx_q.e[i].urb = usb_alloc_urb(0, GFP_KERNEL);
		dev->rx_q.e[i].p = dev_alloc_pages(MT_RX_ORDER);

		if (!dev->rx_q.e[i].urb || !dev->rx_q.e[i].p)
			return -ENOMEM;
	}

	return 0;
}
