tlv320aic23b_probe(struct i2c_client *client,
			      const struct i2c_device_id *id)
{
	struct tlv320aic23b_state *state;
	struct v4l2_subdev *sd;


	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = devm_kzalloc(&client->dev, sizeof(*state), GFP_KERNEL);
	if (state == NULL)
		return -ENOMEM;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &tlv320aic23b_ops);


	tlv320aic23b_write(sd, 15, 0x000);

	tlv320aic23b_write(sd, 6, 0x00A);

	tlv320aic23b_write(sd, 7, 0x049);

	tlv320aic23b_write(sd, 0, 0x119);

	tlv320aic23b_write(sd, 8, 0x000);

	tlv320aic23b_write(sd, 9, 0x001);

	v4l2_ctrl_handler_init(&state->hdl, 1);
	v4l2_ctrl_new_std(&state->hdl, &tlv320aic23b_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	sd->ctrl_handler = &state->hdl;
	if (state->hdl.error) {
		int err = state->hdl.error;

		v4l2_ctrl_handler_free(&state->hdl);
		return err;
	}
	v4l2_ctrl_handler_setup(&state->hdl);
	return 0;
}
