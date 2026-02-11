gp2a_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	const struct gp2a_platform_data *pdata = dev_get_platdata(&client->dev);
	struct gp2a_data *dt;
	int error;

	if (!pdata)
		return -EINVAL;

	if (pdata->hw_setup) {
		error = pdata->hw_setup(client);
		if (error < 0)
			return error;
	}

	error = gpio_request_one(pdata->vout_gpio, GPIOF_IN, GP2A_I2C_NAME);
	if (error)
		goto err_hw_shutdown;

	dt = kzalloc(sizeof(struct gp2a_data), GFP_KERNEL);
	if (!dt) {
		error = -ENOMEM;
		goto err_free_gpio;
	}

	dt->pdata = pdata;
	dt->i2c_client = client;

	error = gp2a_initialize(dt);
	if (error < 0)
		goto err_free_mem;

	dt->input = input_allocate_device();
	if (!dt->input) {
		error = -ENOMEM;
		goto err_free_mem;
	}

	input_set_drvdata(dt->input, dt);

	dt->input->open = gp2a_device_open;
	dt->input->close = gp2a_device_close;
	dt->input->name = GP2A_I2C_NAME;
	dt->input->id.bustype = BUS_I2C;
	dt->input->dev.parent = &client->dev;

	input_set_capability(dt->input, EV_SW, SW_FRONT_PROXIMITY);

	error = request_threaded_irq(client->irq, NULL, gp2a_irq,
			IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING |
				IRQF_ONESHOT,
			GP2A_I2C_NAME, dt);
	if (error) {
		dev_err(&client->dev, "irq request failed\n");
		goto err_free_input_dev;
	}

	error = input_register_device(dt->input);
	if (error) {
		dev_err(&client->dev, "device registration failed\n");
		goto err_free_irq;
	}

	device_init_wakeup(&client->dev, pdata->wakeup);
	i2c_set_clientdata(client, dt);

	return 0;

err_free_irq:
	free_irq(client->irq, dt);
err_free_input_dev:
	input_free_device(dt->input);
err_free_mem:
	kfree(dt);
err_free_gpio:
	gpio_free(pdata->vout_gpio);
err_hw_shutdown:
	if (pdata->hw_shutdown)
		pdata->hw_shutdown(client);
	return error;
}
