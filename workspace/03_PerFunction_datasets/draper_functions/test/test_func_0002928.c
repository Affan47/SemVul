search_serial_device(
					struct usb_interface *iface)
{
	const struct usb_device_id *id = NULL;
	struct usb_serial_driver *drv;
	struct usb_driver *driver = to_usb_driver(iface->dev.driver);


	list_for_each_entry(drv, &usb_serial_driver_list, driver_list) {
		if (drv->usb_driver == driver)
			id = get_iface_id(drv, iface);
		if (id)
			return drv;
	}

	return NULL;
}
