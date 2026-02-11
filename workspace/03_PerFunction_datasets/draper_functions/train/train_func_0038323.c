imon_init_display(struct imon_context *ictx,
			      struct usb_interface *intf)
{
	int ret;

	dev_dbg(ictx->dev, "Registering iMON display with sysfs\n");


	ret = sysfs_create_group(&intf->dev.kobj, &imon_display_attr_group);
	if (ret)
		dev_err(ictx->dev, "Could not create display sysfs "
			"entries(%d)", ret);

	if (ictx->display_type == IMON_DISPLAY_TYPE_LCD)
		ret = usb_register_dev(intf, &imon_lcd_class);
	else
		ret = usb_register_dev(intf, &imon_vfd_class);
	if (ret)

		dev_info(ictx->dev, "could not get a minor number for "
			 "display\n");

}
