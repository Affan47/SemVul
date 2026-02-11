kingsun_net_open(struct net_device *netdev)
{
	struct kingsun_cb *kingsun = netdev_priv(netdev);
	int err = -ENOMEM;
	char hwname[16];


	kingsun->receiving = 0;


	kingsun->rx_buff.in_frame = FALSE;
	kingsun->rx_buff.state = OUTSIDE_FRAME;
	kingsun->rx_buff.truesize = IRDA_SKB_MAX_MTU;
	kingsun->rx_buff.skb = dev_alloc_skb(IRDA_SKB_MAX_MTU);
	if (!kingsun->rx_buff.skb)
		goto free_mem;

	skb_reserve(kingsun->rx_buff.skb, 1);
	kingsun->rx_buff.head = kingsun->rx_buff.skb->data;

	kingsun->rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!kingsun->rx_urb)
		goto free_mem;

	kingsun->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!kingsun->tx_urb)
		goto free_mem;


	sprintf(hwname, "usb#%d", kingsun->usbdev->devnum);
	kingsun->irlap = irlap_open(netdev, &kingsun->qos, hwname);
	if (!kingsun->irlap) {
		dev_err(&kingsun->usbdev->dev, "irlap_open failed\n");
		goto free_mem;
	}


	usb_fill_int_urb(kingsun->rx_urb, kingsun->usbdev,
			  usb_rcvintpipe(kingsun->usbdev, kingsun->ep_in),
			  kingsun->in_buf, kingsun->max_rx,
			  kingsun_rcv_irq, kingsun, 1);
	kingsun->rx_urb->status = 0;
	err = usb_submit_urb(kingsun->rx_urb, GFP_KERNEL);
	if (err) {
		dev_err(&kingsun->usbdev->dev,
			"first urb-submit failed: %d\n", err);
		goto close_irlap;
	}

	netif_start_queue(netdev);


	return 0;

 close_irlap:
	irlap_close(kingsun->irlap);
 free_mem:
	if (kingsun->tx_urb) {
		usb_free_urb(kingsun->tx_urb);
		kingsun->tx_urb = NULL;
	}
	if (kingsun->rx_urb) {
		usb_free_urb(kingsun->rx_urb);
		kingsun->rx_urb = NULL;
	}
	if (kingsun->rx_buff.skb) {
		kfree_skb(kingsun->rx_buff.skb);
		kingsun->rx_buff.skb = NULL;
		kingsun->rx_buff.head = NULL;
	}
	return err;
}
