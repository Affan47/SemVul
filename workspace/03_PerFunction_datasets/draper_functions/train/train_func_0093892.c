bt866_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct bt866 *encoder;
	struct v4l2_subdev *sd;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	encoder = devm_kzalloc(&client->dev, sizeof(*encoder), GFP_KERNEL);
	if (encoder == NULL)
		return -ENOMEM;
	sd = &encoder->sd;
	v4l2_i2c_subdev_init(sd, client, &bt866_ops);
	return 0;
}
