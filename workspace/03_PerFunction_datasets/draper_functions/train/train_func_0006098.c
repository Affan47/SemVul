usb_remove_newid_files(struct usb_driver *usb_drv)
{
	if (usb_drv->no_dynamic_id)
		return;

	if (usb_drv->probe != NULL) {
		driver_remove_file(&usb_drv->drvwrap.driver,
				&driver_attr_remove_id);
		driver_remove_file(&usb_drv->drvwrap.driver,
				   &driver_attr_new_id);
	}
}
