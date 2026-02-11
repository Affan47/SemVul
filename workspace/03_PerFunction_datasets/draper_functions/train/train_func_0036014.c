sms_ir_init(struct smscore_device_t *coredev)
{
	int err;
	int board_id = smscore_get_board_id(coredev);
	struct rc_dev *dev;

	pr_debug("Allocating rc device\n");
	dev = rc_allocate_device();
	if (!dev)
		return -ENOMEM;

	coredev->ir.controller = 0;
	coredev->ir.timeout = IR_DEFAULT_TIMEOUT;
	pr_debug("IR port %d, timeout %d ms\n",
			coredev->ir.controller, coredev->ir.timeout);

	snprintf(coredev->ir.name, sizeof(coredev->ir.name),
		 "SMS IR (%s)", sms_get_board(board_id)->name);

	strlcpy(coredev->ir.phys, coredev->devpath, sizeof(coredev->ir.phys));
	strlcat(coredev->ir.phys, "/ir0", sizeof(coredev->ir.phys));

	dev->input_name = coredev->ir.name;
	dev->input_phys = coredev->ir.phys;
	dev->dev.parent = coredev->device;

#if 0

	dev->input_id.bustype = BUS_USB;
	dev->input_id.version = 1;
	dev->input_id.vendor = le16_to_cpu(dev->udev->descriptor.idVendor);
	dev->input_id.product = le16_to_cpu(dev->udev->descriptor.idProduct);
#endif

	dev->priv = coredev;
	dev->driver_type = RC_DRIVER_IR_RAW;
	dev->allowed_protocols = RC_BIT_ALL;
	dev->map_name = sms_get_board(board_id)->rc_codes;
	dev->driver_name = MODULE_NAME;

	pr_debug("Input device (IR) %s is set for key events\n",
		 dev->input_name);

	err = rc_register_device(dev);
	if (err < 0) {
		pr_err("Failed to register device\n");
		rc_free_device(dev);
		return err;
	}

	coredev->ir.dev = dev;
	return 0;
}
