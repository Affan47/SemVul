generic_resume(struct usb_device *udev, pm_message_t msg)
{
	int rc;


	if (!udev->parent)
		rc = hcd_bus_resume(udev, msg);
	else
		rc = usb_port_resume(udev, msg);
	return rc;
}
