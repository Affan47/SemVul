ps8622_remove(struct i2c_client *client)
{
	struct ps8622_bridge *ps8622 = i2c_get_clientdata(client);

	if (ps8622->bl)
		backlight_device_unregister(ps8622->bl);

	drm_bridge_remove(&ps8622->bridge);

	return 0;
}
