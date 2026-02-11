sierra_net_probe(struct usb_interface *udev, const struct usb_device_id *prod)
{
	int ret;

	ret = usbnet_probe(udev, prod);
	if (ret == 0) {
		struct usbnet *dev = usb_get_intfdata(udev);

		ret = usbnet_status_start(dev, GFP_KERNEL);
		if (ret == 0) {

			sierra_net_dosync(dev);
		}
	}
	return ret;
}
