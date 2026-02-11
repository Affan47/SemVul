tm6000_irq_callback(struct urb *urb)
{
	struct tm6000_dmaqueue  *dma_q = urb->context;
	struct tm6000_core *dev = container_of(dma_q, struct tm6000_core, vidq);
	int i;

	switch (urb->status) {
	case 0:
	case -ETIMEDOUT:
		break;

	case -ECONNRESET:
	case -ENOENT:
	case -ESHUTDOWN:
		return;

	default:
		tm6000_err("urb completion error %d.\n", urb->status);
		break;
	}

	spin_lock(&dev->slock);
	tm6000_isoc_copy(urb);
	spin_unlock(&dev->slock);


	for (i = 0; i < urb->number_of_packets; i++) {
		urb->iso_frame_desc[i].status = 0;
		urb->iso_frame_desc[i].actual_length = 0;
	}

	urb->status = usb_submit_urb(urb, GFP_ATOMIC);
	if (urb->status)
		tm6000_err("urb resubmit failed (error=%i)\n",
			urb->status);
}
