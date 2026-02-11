lis3lv02d_i2c_probe(struct i2c_client *client,
					const struct i2c_device_id *id)
{
	int ret = 0;
	struct lis3lv02d_platform_data *pdata = client->dev.platform_data;

#ifdef CONFIG_OF
	if (of_match_device(lis3lv02d_i2c_dt_ids, &client->dev)) {
		lis3_dev.of_node = client->dev.of_node;
		ret = lis3lv02d_init_dt(&lis3_dev);
		if (ret)
			return ret;
		pdata = lis3_dev.pdata;
	}
#endif

	if (pdata) {
		if ((pdata->driver_features & LIS3_USE_BLOCK_READ) &&
			(i2c_check_functionality(client->adapter,
						I2C_FUNC_SMBUS_I2C_BLOCK)))
			lis3_dev.blkread  = lis3_i2c_blockread;

		if (pdata->axis_x)
			lis3lv02d_axis_map.x = pdata->axis_x;

		if (pdata->axis_y)
			lis3lv02d_axis_map.y = pdata->axis_y;

		if (pdata->axis_z)
			lis3lv02d_axis_map.z = pdata->axis_z;

		if (pdata->setup_resources)
			ret = pdata->setup_resources();

		if (ret)
			goto fail;
	}

	lis3_dev.regulators[0].supply = reg_vdd;
	lis3_dev.regulators[1].supply = reg_vdd_io;
	ret = regulator_bulk_get(&client->dev,
				 ARRAY_SIZE(lis3_dev.regulators),
				 lis3_dev.regulators);
	if (ret < 0)
		goto fail;

	lis3_dev.pdata	  = pdata;
	lis3_dev.bus_priv = client;
	lis3_dev.init	  = lis3_i2c_init;
	lis3_dev.read	  = lis3_i2c_read;
	lis3_dev.write	  = lis3_i2c_write;
	lis3_dev.irq	  = client->irq;
	lis3_dev.ac	  = lis3lv02d_axis_map;
	lis3_dev.pm_dev	  = &client->dev;

	i2c_set_clientdata(client, &lis3_dev);


	lis3_reg_ctrl(&lis3_dev, LIS3_REG_ON);

	ret = lis3lv02d_init_device(&lis3_dev);

	lis3_reg_ctrl(&lis3_dev, LIS3_REG_OFF);

	if (ret)
		goto fail2;
	return 0;

fail2:
	regulator_bulk_free(ARRAY_SIZE(lis3_dev.regulators),
				lis3_dev.regulators);
fail:
	if (pdata && pdata->release_resources)
		pdata->release_resources();
	return ret;
}
