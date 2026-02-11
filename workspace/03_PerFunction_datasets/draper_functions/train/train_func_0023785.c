elants_i2c_suspend(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct elants_data *ts = i2c_get_clientdata(client);
	const u8 set_sleep_cmd[] = { 0x54, 0x50, 0x00, 0x01 };
	int retry_cnt;
	int error;


	if (ts->iap_mode != ELAN_IAP_OPERATIONAL)
		return -EBUSY;

	disable_irq(client->irq);

	if (device_may_wakeup(dev)) {


		ts->wake_irq_enabled = (enable_irq_wake(client->irq) == 0);
	} else if (ts->keep_power_in_suspend) {
		for (retry_cnt = 0; retry_cnt < MAX_RETRIES; retry_cnt++) {
			error = elants_i2c_send(client, set_sleep_cmd,
						sizeof(set_sleep_cmd));
			if (!error)
				break;

			dev_err(&client->dev,
				"suspend command failed: %d\n", error);
		}
	} else {
		elants_i2c_power_off(ts);
	}

	return 0;
}
