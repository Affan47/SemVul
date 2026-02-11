usb_remove_sysfs_intf_files(struct usb_interface *intf)
{
	if (!intf->sysfs_files_created)
		return;

	device_remove_file(&intf->dev, &dev_attr_interface);
	intf->sysfs_files_created = 0;
}
