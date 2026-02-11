ths8200_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct ths8200_state *decoder = to_state(sd);

	v4l2_dbg(1, debug, sd, "%s removed @ 0x%x (%s)\n", client->name,
		 client->addr << 1, client->adapter->name);

	ths8200_s_power(sd, false);
	v4l2_async_unregister_subdev(&decoder->sd);

	return 0;
}
