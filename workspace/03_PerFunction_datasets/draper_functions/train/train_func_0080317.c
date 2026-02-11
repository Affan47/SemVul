ti_startup(struct usb_serial *serial)
{
	struct ti_device *tdev;
	struct usb_device *dev = serial->dev;
	int status;

	dev_dbg(&dev->dev,
		"%s - product 0x%4X, num configurations %d, configuration value %d\n",
		__func__, le16_to_cpu(dev->descriptor.idProduct),
		dev->descriptor.bNumConfigurations,
		dev->actconfig->desc.bConfigurationValue);


	tdev = kzalloc(sizeof(struct ti_device), GFP_KERNEL);
	if (!tdev)
		return -ENOMEM;

	mutex_init(&tdev->td_open_close_lock);
	tdev->td_serial = serial;
	usb_set_serial_data(serial, tdev);


	if (serial->type == &ti_1port_device)
		tdev->td_is_3410 = 1;
	dev_dbg(&dev->dev, "%s - device type is %s\n", __func__,
		tdev->td_is_3410 ? "3410" : "5052");


	if (dev->descriptor.bNumConfigurations == 1) {
		status = ti_download_firmware(tdev);

		if (status != 0)
			goto free_tdev;


		if (tdev->td_is_3410) {
			msleep_interruptible(100);
			usb_reset_device(dev);
		}

		status = -ENODEV;
		goto free_tdev;
	}


	if (dev->actconfig->desc.bConfigurationValue == TI_BOOT_CONFIG) {
		status = usb_driver_set_configuration(dev, TI_ACTIVE_CONFIG);
		status = status ? status : -ENODEV;
		goto free_tdev;
	}

	if (serial->num_bulk_in < serial->num_ports ||
			serial->num_bulk_out < serial->num_ports) {
		dev_err(&serial->interface->dev, "missing endpoints\n");
		status = -ENODEV;
		goto free_tdev;
	}

	return 0;

free_tdev:
	kfree(tdev);
	usb_set_serial_data(serial, NULL);
	return status;
}
