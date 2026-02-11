tw9910_video_probe(struct i2c_client *client)
{
	struct tw9910_priv *priv = to_tw9910(client);
	s32 id;
	int ret;


	if (SOCAM_DATAWIDTH_16 != priv->info->buswidth &&
	    SOCAM_DATAWIDTH_8  != priv->info->buswidth) {
		dev_err(&client->dev, "bus width error\n");
		return -ENODEV;
	}

	ret = tw9910_s_power(&priv->subdev, 1);
	if (ret < 0)
		return ret;


	id = i2c_smbus_read_byte_data(client, ID);
	priv->revision = GET_REV(id);
	id = GET_ID(id);

	if (0x0B != id ||
	    0x01 < priv->revision) {
		dev_err(&client->dev,
			"Product ID error %x:%x\n",
			id, priv->revision);
		ret = -ENODEV;
		goto done;
	}

	dev_info(&client->dev,
		 "tw9910 Product ID %0x:%0x\n", id, priv->revision);

	priv->norm = V4L2_STD_NTSC;
	priv->scale = &tw9910_ntsc_scales[0];

done:
	tw9910_s_power(&priv->subdev, 0);
	return ret;
}
