stir_rcv_irq(struct urb *urb)
{
	struct stir_cb *stir = urb->context;
	int err;


	if (!netif_running(stir->netdev))
		return;


	if (urb->status != 0)
		return;

	if (urb->actual_length > 0) {
		pr_debug("receive %d\n", urb->actual_length);
		unwrap_chars(stir, urb->transfer_buffer,
			     urb->actual_length);

		stir->rx_time = ktime_get();
	}


	if (!stir->receiving)
		return;


	err = usb_submit_urb(urb, GFP_ATOMIC);


	if (err) {
		dev_warn(&stir->netdev->dev, "usb receive submit error: %d\n",
			 err);
		stir->receiving = 0;
		wake_up_process(stir->thread);
	}
}
