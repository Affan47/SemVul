ov5642_set_resolution(struct v4l2_subdev *sd)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ov5642 *priv = to_ov5642(client);
	int width = priv->crop_rect.width;
	int height = priv->crop_rect.height;
	int total_width = priv->total_width;
	int total_height = priv->total_height;
	int start_x = (OV5642_SENSOR_SIZE_X - width) / 2;
	int start_y = (OV5642_SENSOR_SIZE_Y - height) / 2;
	int ret;


	ret = reg_write16(client, REG_WINDOW_START_X_HIGH, start_x);
	if (!ret)
		ret = reg_write16(client, REG_WINDOW_START_Y_HIGH, start_y);
	if (!ret) {
		priv->crop_rect.left = start_x;
		priv->crop_rect.top = start_y;
	}

	if (!ret)
		ret = reg_write16(client, REG_WINDOW_WIDTH_HIGH, width);
	if (!ret)
		ret = reg_write16(client, REG_WINDOW_HEIGHT_HIGH, height);
	if (ret)
		return ret;
	priv->crop_rect.width = width;
	priv->crop_rect.height = height;


	ret = reg_write16(client, REG_OUT_WIDTH_HIGH, width);
	if (!ret)
		ret = reg_write16(client, REG_OUT_HEIGHT_HIGH, height);


	if (!ret)
		ret = reg_write16(client, REG_OUT_TOTAL_WIDTH_HIGH, total_width);
	if (!ret)
		ret = reg_write16(client, REG_OUT_TOTAL_HEIGHT_HIGH, total_height);


	if (!ret)
		ret = reg_write16(client, REG_AVG_WINDOW_END_X_HIGH, width);
	if (!ret)
		ret = reg_write16(client, REG_AVG_WINDOW_END_Y_HIGH, height);

	return ret;
}
