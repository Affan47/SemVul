dme1737_isa_probe(struct platform_device *pdev)
{
	u8 company, device;
	struct resource *res;
	struct dme1737_data *data;
	struct device *dev = &pdev->dev;
	int err;

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!devm_request_region(dev, res->start, DME1737_EXTENT, "dme1737")) {
		dev_err(dev, "Failed to request region 0x%04x-0x%04x.\n",
			(unsigned short)res->start,
			(unsigned short)res->start + DME1737_EXTENT - 1);
		return -EBUSY;
	}

	data = devm_kzalloc(dev, sizeof(struct dme1737_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->addr = res->start;
	platform_set_drvdata(pdev, data);


	switch (force_id) {
	case SCH3112_ID:
	case SCH3114_ID:
	case SCH3116_ID:
		data->type = sch311x;
		break;
	case SCH5127_ID:
		data->type = sch5127;
		break;
	default:
		company = dme1737_read(data, DME1737_REG_COMPANY);
		device = dme1737_read(data, DME1737_REG_DEVICE);

		if ((company == DME1737_COMPANY_SMSC) &&
		    (device == SCH311X_DEVICE)) {
			data->type = sch311x;
		} else if ((company == DME1737_COMPANY_SMSC) &&
			   (device == SCH5127_DEVICE)) {
			data->type = sch5127;
		} else {
			return -ENODEV;
		}
	}

	if (data->type == sch5127)
		data->name = "sch5127";
	else
		data->name = "sch311x";


	mutex_init(&data->update_lock);

	dev_info(dev, "Found a %s chip at 0x%04x\n",
		 data->type == sch5127 ? "SCH5127" : "SCH311x", data->addr);


	err = dme1737_init_device(dev);
	if (err) {
		dev_err(dev, "Failed to initialize device.\n");
		return err;
	}


	err = dme1737_create_files(dev);
	if (err) {
		dev_err(dev, "Failed to create sysfs files.\n");
		return err;
	}


	data->hwmon_dev = hwmon_device_register(dev);
	if (IS_ERR(data->hwmon_dev)) {
		dev_err(dev, "Failed to register device.\n");
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove_files;
	}

	return 0;

exit_remove_files:
	dme1737_remove_files(dev);
	return err;
}
