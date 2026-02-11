lan78xx_rx_bh(struct lan78xx_net *dev)
{
	struct urb *urb;
	int i;

	if (skb_queue_len(&dev->rxq) < dev->rx_qlen) {
		for (i = 0; i < 10; i++) {
			if (skb_queue_len(&dev->rxq) >= dev->rx_qlen)
				break;
			urb = usb_alloc_urb(0, GFP_ATOMIC);
			if (urb)
				if (rx_submit(dev, urb, GFP_ATOMIC) == -ENOLINK)
					return;
		}

		if (skb_queue_len(&dev->rxq) < dev->rx_qlen)
			tasklet_schedule(&dev->bh);
	}
	if (skb_queue_len(&dev->txq) < dev->tx_qlen)
		netif_wake_queue(dev->net);
}
