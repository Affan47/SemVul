usb_device_match(struct device *dev, struct device_driver *drv)
{

	if (is_usb_device(dev)) {


		if (!is_usb_device_driver(drv))
			return 0;


		return 1;

	} else if (is_usb_interface(dev)) {
		struct usb_interface *intf;
		struct usb_driver *usb_drv;
		const struct usb_device_id *id;


		if (is_usb_device_driver(drv))
			return 0;

		intf = to_usb_interface(dev);
		usb_drv = to_usb_driver(drv);

		id = usb_match_id(intf, usb_drv->id_table);
		if (id)
			return 1;

		id = usb_match_dynamic_id(intf, usb_drv);
		if (id)
			return 1;
	}

	return 0;
}
