xpad_disconnect(struct usb_interface *intf)
{
	struct usb_xpad *xpad = usb_get_intfdata (intf);

	xpad_deinit_input(xpad);
	xpad_deinit_output(xpad);

	if (xpad->xtype == XTYPE_XBOX360W) {
		usb_kill_urb(xpad->irq_in);
	}

	usb_free_urb(xpad->irq_in);
	usb_free_coherent(xpad->udev, XPAD_PKT_LEN,
			xpad->idata, xpad->idata_dma);

	kfree(xpad);

	usb_set_intfdata(intf, NULL);
}
