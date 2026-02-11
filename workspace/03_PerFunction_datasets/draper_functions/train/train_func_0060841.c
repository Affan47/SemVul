cy8ctmg110_suspend(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct cy8ctmg110 *ts = i2c_get_clientdata(client);

	if (device_may_wakeup(&client->dev))
		enable_irq_wake(client->irq);
	else {
		cy8ctmg110_set_sleepmode(ts, true);
		cy8ctmg110_power(ts, false);
	}
	return 0;
}
