kingsun_rcv_irq(struct urb *urb)
{
	struct kingsun_cb *kingsun = urb->context;
	int ret;


	if (!netif_running(kingsun->netdev)) {
		kingsun->receiving = 0;
		return;
	}


	if (urb->status != 0) {
		dev_err(&kingsun->usbdev->dev,
			"kingsun_rcv_irq: urb asynchronously failed - %d\n",
			urb->status);
		kingsun->receiving = 0;
		return;
	}

	if (urb->actual_length == kingsun->max_rx) {
		__u8 *bytes = urb->transfer_buffer;
		int i;


		if (bytes[0] >= 1 && bytes[0] < kingsun->max_rx) {
			for (i = 1; i <= bytes[0]; i++) {
				async_unwrap_char(kingsun->netdev,
						  &kingsun->netdev->stats,
						  &kingsun->rx_buff, bytes[i]);
			}
			kingsun->receiving =
				(kingsun->rx_buff.state != OUTSIDE_FRAME)
				? 1 : 0;
		}
	} else if (urb->actual_length > 0) {
		dev_err(&kingsun->usbdev->dev,
			"%s(): Unexpected response length, expected %d got %d\n",
			__func__, kingsun->max_rx, urb->actual_length);
	}

	ret = usb_submit_urb(urb, GFP_ATOMIC);
}
