usb_forced_unbind_intf(struct usb_interface *intf)
{
	struct usb_driver *driver = to_usb_driver(intf->dev.driver);

	dev_dbg(&intf->dev, "forced unbind\n");
	usb_driver_release_interface(driver, intf);


	intf->needs_binding = 1;
}
