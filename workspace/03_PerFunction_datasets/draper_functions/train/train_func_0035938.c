adv7175_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int i;
	struct adv7175 *encoder;
	struct v4l2_subdev *sd;


	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	encoder = devm_kzalloc(&client->dev, sizeof(*encoder), GFP_KERNEL);
	if (encoder == NULL)
		return -ENOMEM;
	sd = &encoder->sd;
	v4l2_i2c_subdev_init(sd, client, &adv7175_ops);
	encoder->norm = V4L2_STD_NTSC;
	encoder->input = 0;

	i = adv7175_write_block(sd, init_common, sizeof(init_common));
	if (i >= 0) {
		i = adv7175_write(sd, 0x07, TR0MODE | TR0RST);
		i = adv7175_write(sd, 0x07, TR0MODE);
		i = adv7175_read(sd, 0x12);
		v4l2_dbg(1, debug, sd, "revision %d\n", i & 1);
	}
	if (i < 0)
		v4l2_dbg(1, debug, sd, "init error 0x%x\n", i);
	return 0;
}
