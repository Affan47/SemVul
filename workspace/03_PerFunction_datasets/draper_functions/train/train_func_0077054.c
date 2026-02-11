sbs_suspend(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct sbs_info *chip = i2c_get_clientdata(client);
	s32 ret;

	if (chip->poll_time > 0)
		cancel_delayed_work_sync(&chip->work);


	ret = sbs_write_word_data(client, sbs_data[REG_MANUFACTURER_DATA].addr,
		MANUFACTURER_ACCESS_SLEEP);
	if (chip->is_present && ret < 0)
		return ret;

	return 0;
}
