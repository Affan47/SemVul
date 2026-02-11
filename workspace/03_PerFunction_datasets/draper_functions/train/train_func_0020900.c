usbutil_list(void)
{
	const struct usb_bus *bus;

	for (bus = usb_get_busses(); bus; bus = bus->next) {
		const struct usb_device *dev;
		int busnum = atoi(bus->dirname);

		printc("Devices on bus %03d:\n", busnum);

		for (dev = bus->devices; dev; dev = dev->next) {
			int devnum = atoi(dev->filename);

			printc("    %03d:%03d %04x:%04x %s\n",
			       busnum, devnum,
			       dev->descriptor.idVendor,
			       dev->descriptor.idProduct,
			       device_help(dev));
		}
	}
}
