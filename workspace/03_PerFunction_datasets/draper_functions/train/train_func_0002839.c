rf2500_open(const char *devpath)
{
	struct rf2500_transport *tr = malloc(sizeof(*tr));
	struct usb_device *dev;
	char buf[64];

	if (!tr) {
		pr_error("rf2500: can't allocate memory");
		return NULL;
	}

	tr->base.destroy = usbtr_destroy;
	tr->base.send = usbtr_send;
	tr->base.recv = usbtr_recv;

	usb_init();
	usb_find_busses();
	usb_find_devices();

	if (devpath)
		dev = usbutil_find_by_loc(devpath);
	else
		dev = usbutil_find_by_id(USB_FET_VENDOR, USB_FET_PRODUCT);

	if (!dev) {
		free(tr);
		return NULL;
	}

	if (open_device(tr, dev) < 0) {
		printc_err("rf2500: failed to open RF2500 device\n");
		return NULL;
	}


#ifndef __APPLE__
	while (usb_bulk_read(tr->handle, USB_FET_IN_EP,
			     buf, sizeof(buf),
			     100) >= 0);
#endif

	return (transport_t)tr;
}
