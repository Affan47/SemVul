abb5zes3_remove(struct i2c_client *client)
{
	struct abb5zes3_rtc_data *rtc_data = dev_get_drvdata(&client->dev);

	if (rtc_data->irq > 0)
		device_init_wakeup(&client->dev, false);

	return 0;
}
