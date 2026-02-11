ov9640_video_probe(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct ov9640_priv *priv = to_ov9640_sensor(sd);
	u8		pid, ver, midh, midl;
	const char	*devname;
	int		ret;

	ret = ov9640_s_power(&priv->subdev, 1);
	if (ret < 0)
		return ret;


	ret = ov9640_reg_read(client, OV9640_PID, &pid);
	if (!ret)
		ret = ov9640_reg_read(client, OV9640_VER, &ver);
	if (!ret)
		ret = ov9640_reg_read(client, OV9640_MIDH, &midh);
	if (!ret)
		ret = ov9640_reg_read(client, OV9640_MIDL, &midl);
	if (ret)
		goto done;

	switch (VERSION(pid, ver)) {
	case OV9640_V2:
		devname		= "ov9640";
		priv->revision	= 2;
		break;
	case OV9640_V3:
		devname		= "ov9640";
		priv->revision	= 3;
		break;
	default:
		dev_err(&client->dev, "Product ID error %x:%x\n", pid, ver);
		ret = -ENODEV;
		goto done;
	}

	dev_info(&client->dev, "%s Product ID %0x:%0x Manufacturer ID %x:%x\n",
		 devname, pid, ver, midh, midl);

	ret = v4l2_ctrl_handler_setup(&priv->hdl);

done:
	ov9640_s_power(&priv->subdev, 0);
	return ret;
}
