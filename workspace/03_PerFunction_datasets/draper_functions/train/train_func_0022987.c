go7007_usb_read_interrupt(struct go7007 *go)
{
	struct go7007_usb *usb = go->hpi_context;
	int r;

	r = usb_submit_urb(usb->intr_urb, GFP_KERNEL);
	if (r < 0) {
		dev_err(go->dev, "unable to submit interrupt urb: %d\n", r);
		return r;
	}
	return 0;
}
