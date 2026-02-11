rs5c372_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	int err = 0;
	int smbus_mode = 0;
	struct rs5c372 *rs5c372;
	struct rtc_time tm;

	dev_dbg(&client->dev, "%s\n", __func__);

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C |
			I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_I2C_BLOCK)) {


		if (i2c_check_functionality(client->adapter,
				I2C_FUNC_SMBUS_BYTE_DATA |
				I2C_FUNC_SMBUS_I2C_BLOCK))
			smbus_mode = 1;
		else {

			err = -ENODEV;
			goto exit;
		}
	}

	rs5c372 = devm_kzalloc(&client->dev, sizeof(struct rs5c372),
				GFP_KERNEL);
	if (!rs5c372) {
		err = -ENOMEM;
		goto exit;
	}

	rs5c372->client = client;
	i2c_set_clientdata(client, rs5c372);
	rs5c372->type = id->driver_data;


	rs5c372->regs = &rs5c372->buf[1];
	rs5c372->smbus = smbus_mode;

	err = rs5c_get_regs(rs5c372);
	if (err < 0)
		goto exit;


	switch (rs5c372->type) {
	case rtc_rs5c372a:
	case rtc_rs5c372b:


		if (rs5c372->regs[RS5C_REG_CTRL2] & RS5C372_CTRL2_24)
			rs5c372->time24 = 1;
		break;
	case rtc_r2025sd:
	case rtc_r2221tl:
	case rtc_rv5c386:
	case rtc_rv5c387a:
		if (rs5c372->regs[RS5C_REG_CTRL1] & RV5C387_CTRL1_24)
			rs5c372->time24 = 1;


		break;
	default:
		dev_err(&client->dev, "unknown RTC type\n");
		goto exit;
	}


	err = rs5c_oscillator_setup(rs5c372);
	if (unlikely(err < 0)) {
		dev_err(&client->dev, "setup error\n");
		goto exit;
	}

	if (rs5c372_get_datetime(client, &tm) < 0)
		dev_warn(&client->dev, "clock needs to be set\n");

	dev_info(&client->dev, "%s found, %s, driver version " DRV_VERSION "\n",
			({ char *s; switch (rs5c372->type) {
			case rtc_r2025sd:	s = "r2025sd"; break;
			case rtc_r2221tl:	s = "r2221tl"; break;
			case rtc_rs5c372a:	s = "rs5c372a"; break;
			case rtc_rs5c372b:	s = "rs5c372b"; break;
			case rtc_rv5c386:	s = "rv5c386"; break;
			case rtc_rv5c387a:	s = "rv5c387a"; break;
			default:		s = "chip"; break;
			}; s;}),
			rs5c372->time24 ? "24hr" : "am/pm"
			);


	rs5c372->rtc = devm_rtc_device_register(&client->dev,
					rs5c372_driver.driver.name,
					&rs5c372_rtc_ops, THIS_MODULE);

	if (IS_ERR(rs5c372->rtc)) {
		err = PTR_ERR(rs5c372->rtc);
		goto exit;
	}

	err = rs5c_sysfs_register(&client->dev);
	if (err)
		goto exit;

	return 0;

exit:
	return err;
}
