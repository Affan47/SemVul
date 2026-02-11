synusb_get_in_endpoint(struct usb_host_interface *iface)
{

	struct usb_endpoint_descriptor *endpoint;
	int i;

	for (i = 0; i < iface->desc.bNumEndpoints; ++i) {
		endpoint = &iface->endpoint[i].desc;

		if (usb_endpoint_is_int_in(endpoint)) {

			return endpoint;
		}
	}

	return NULL;
}
