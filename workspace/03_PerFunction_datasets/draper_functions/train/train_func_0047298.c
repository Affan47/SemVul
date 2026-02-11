adp8860_probe(struct i2c_client *client,
					const struct i2c_device_id *id)
{
	struct backlight_device *bl;
	struct adp8860_bl *data;
	struct adp8860_backlight_platform_data *pdata =
		dev_get_platdata(&client->dev);
	struct backlight_properties props;
	uint8_t reg_val;
	int ret;

	if (!i2c_check_functionality(client->adapter,
					I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&client->dev, "SMBUS Byte Data not Supported\n");
		return -EIO;
	}

	if (!pdata) {
		dev_err(&client->dev, "no platform data?\n");
		return -EINVAL;
	}

	data = devm_kzalloc(&client->dev, sizeof(*data), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	ret = adp8860_read(client, ADP8860_MFDVID, &reg_val);
	if (ret < 0)
		return ret;

	switch (ADP8860_MANID(reg_val)) {
	case ADP8863_MANUFID:
		data->gdwn_dis = !!pdata->gdwn_dis;
	case ADP8860_MANUFID:
		data->en_ambl_sens = !!pdata->en_ambl_sens;
		break;
	case ADP8861_MANUFID:
		data->gdwn_dis = !!pdata->gdwn_dis;
		break;
	default:
		dev_err(&client->dev, "failed to probe\n");
		return -ENODEV;
	}


	data->revid = ADP8860_DEVID(reg_val);
	data->client = client;
	data->pdata = pdata;
	data->id = id->driver_data;
	data->current_brightness = 0;
	i2c_set_clientdata(client, data);

	memset(&props, 0, sizeof(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = ADP8860_MAX_BRIGHTNESS;

	mutex_init(&data->lock);

	bl = devm_backlight_device_register(&client->dev,
				dev_driver_string(&client->dev),
				&client->dev, data, &adp8860_bl_ops, &props);
	if (IS_ERR(bl)) {
		dev_err(&client->dev, "failed to register backlight\n");
		return PTR_ERR(bl);
	}

	bl->props.brightness = ADP8860_MAX_BRIGHTNESS;

	data->bl = bl;

	if (data->en_ambl_sens)
		ret = sysfs_create_group(&bl->dev.kobj,
			&adp8860_bl_attr_group);

	if (ret) {
		dev_err(&client->dev, "failed to register sysfs\n");
		return ret;
	}

	ret = adp8860_bl_setup(bl);
	if (ret) {
		ret = -EIO;
		goto out;
	}

	backlight_update_status(bl);

	dev_info(&client->dev, "%s Rev.%d Backlight\n",
		client->name, data->revid);

	if (pdata->num_leds)
		adp8860_led_probe(client);

	return 0;

out:
	if (data->en_ambl_sens)
		sysfs_remove_group(&data->bl->dev.kobj,
			&adp8860_bl_attr_group);

	return ret;
}
