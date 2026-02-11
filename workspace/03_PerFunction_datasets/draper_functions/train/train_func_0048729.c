mt9t001_s_stream(struct v4l2_subdev *subdev, int enable)
{
	const u16 mode = MT9T001_OUTPUT_CONTROL_CHIP_ENABLE;
	struct i2c_client *client = v4l2_get_subdevdata(subdev);
	struct mt9t001_platform_data *pdata = client->dev.platform_data;
	struct mt9t001 *mt9t001 = to_mt9t001(subdev);
	struct v4l2_mbus_framefmt *format = &mt9t001->format;
	struct v4l2_rect *crop = &mt9t001->crop;
	unsigned int hratio;
	unsigned int vratio;
	int ret;

	if (!enable)
		return mt9t001_set_output_control(mt9t001, mode, 0);


	if (pdata->clk_pol) {
		ret  = mt9t001_write(client, MT9T001_PIXEL_CLOCK,
				     MT9T001_PIXEL_CLOCK_INVERT);
		if (ret < 0)
			return ret;
	}


	hratio = DIV_ROUND_CLOSEST(crop->width, format->width);
	vratio = DIV_ROUND_CLOSEST(crop->height, format->height);

	ret = mt9t001_write(client, MT9T001_ROW_ADDRESS_MODE, hratio - 1);
	if (ret < 0)
		return ret;

	ret = mt9t001_write(client, MT9T001_COLUMN_ADDRESS_MODE, vratio - 1);
	if (ret < 0)
		return ret;

	ret = mt9t001_write(client, MT9T001_COLUMN_START, crop->left);
	if (ret < 0)
		return ret;

	ret = mt9t001_write(client, MT9T001_ROW_START, crop->top);
	if (ret < 0)
		return ret;

	ret = mt9t001_write(client, MT9T001_WINDOW_WIDTH, crop->width - 1);
	if (ret < 0)
		return ret;

	ret = mt9t001_write(client, MT9T001_WINDOW_HEIGHT, crop->height - 1);
	if (ret < 0)
		return ret;


	return mt9t001_set_output_control(mt9t001, 0, mode);
}
