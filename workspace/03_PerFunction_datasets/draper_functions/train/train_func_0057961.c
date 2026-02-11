gdm_usb_disconnect(struct usb_interface *intf)
{
	u8 bConfigurationValue;
	struct phy_dev *phy_dev;
	struct usbwm_dev *udev;
	u16 idProduct;
	struct usb_device *usbdev = interface_to_usbdev(intf);

	bConfigurationValue = usbdev->actconfig->desc.bConfigurationValue;
	phy_dev = usb_get_intfdata(intf);


	idProduct = le16_to_cpu(usbdev->descriptor.idProduct);

	if (idProduct != EMERGENCY_PID &&
	    bConfigurationValue != DOWNLOAD_CONF_VALUE &&
	    (idProduct & B_DOWNLOAD) == 0) {
		udev = phy_dev->priv_dev;
		udev->usbdev = NULL;

		unregister_wimax_device(phy_dev);
		release_usb(udev);
		kfree(udev);
		kfree(phy_dev);
	}

	usb_put_dev(usbdev);
}
