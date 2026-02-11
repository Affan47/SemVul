ttusbir_bulk_complete(struct urb *urb)
{
	struct ttusbir *tt = urb->context;

	atomic_dec(&tt->led_complete);

	switch (urb->status) {
	case 0:
		break;
	case -ECONNRESET:
	case -ENOENT:
	case -ESHUTDOWN:
		usb_unlink_urb(urb);
		return;
	case -EPIPE:
	default:
		dev_dbg(tt->dev, "Error: urb status = %d\n", urb->status);
		break;
	}

	ttusbir_set_led(tt);
}
