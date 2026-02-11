bq27xxx_battery_i2c_probe(struct i2c_client *client,
				     const struct i2c_device_id *id)
{
	char *name;
	struct bq27xxx_device_info *di;
	int num;
	int retval = 0;


	mutex_lock(&battery_mutex);
	num = idr_alloc(&battery_id, client, 0, 0, GFP_KERNEL);
	mutex_unlock(&battery_mutex);
	if (num < 0)
		return num;

	name = devm_kasprintf(&client->dev, GFP_KERNEL, "%s-%d", id->name, num);
	if (!name) {
		retval = -ENOMEM;
		goto batt_failed;
	}

	di = devm_kzalloc(&client->dev, sizeof(*di), GFP_KERNEL);
	if (!di) {
		retval = -ENOMEM;
		goto batt_failed;
	}

	di->id = num;
	di->dev = &client->dev;
	di->chip = id->driver_data;
	di->bus.read = &bq27xxx_battery_i2c_read;
	di->regs = bq27xxx_regs[di->chip];

	retval = bq27xxx_powersupply_init(di, name);
	if (retval)
		goto batt_failed;


	schedule_delayed_work(&di->work, 60 * HZ);

	i2c_set_clientdata(client, di);

	if (client->irq) {
		retval = devm_request_threaded_irq(&client->dev, client->irq,
				NULL, bq27xxx_battery_irq_handler_thread,
				IRQF_ONESHOT,
				name, di);
		if (retval) {
			dev_err(&client->dev,
				"Unable to register IRQ %d error %d\n",
				client->irq, retval);
			return retval;
		}
	}

	return 0;

batt_failed:
	mutex_lock(&battery_mutex);
	idr_remove(&battery_id, num);
	mutex_unlock(&battery_mutex);

	return retval;
}
