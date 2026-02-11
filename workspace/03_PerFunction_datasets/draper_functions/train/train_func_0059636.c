bd2802_resume(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct bd2802_led *led = i2c_get_clientdata(client);

	if (!bd2802_is_all_off(led) || led->adf_on) {
		bd2802_reset_cancel(led);
		bd2802_restore_state(led);
	}

	return 0;
}
