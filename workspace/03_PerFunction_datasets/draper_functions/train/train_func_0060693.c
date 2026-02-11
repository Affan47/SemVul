mt9v022_s_fmt(struct v4l2_subdev *sd,
			 struct v4l2_mbus_framefmt *mf)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9v022 *mt9v022 = to_mt9v022(client);
	struct v4l2_crop a = {
		.c = {
			.left	= mt9v022->rect.left,
			.top	= mt9v022->rect.top,
			.width	= mf->width,
			.height	= mf->height,
		},
	};
	int ret;


	switch (mf->code) {
	case MEDIA_BUS_FMT_Y8_1X8:
	case MEDIA_BUS_FMT_Y10_1X10:
		if (mt9v022->model != MT9V022IX7ATM)
			return -EINVAL;
		break;
	case MEDIA_BUS_FMT_SBGGR8_1X8:
	case MEDIA_BUS_FMT_SBGGR10_1X10:
		if (mt9v022->model != MT9V022IX7ATC)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}


	ret = mt9v022_s_crop(sd, &a);
	if (!ret) {
		mf->width	= mt9v022->rect.width;
		mf->height	= mt9v022->rect.height;
		mt9v022->fmt	= mt9v022_find_datafmt(mf->code,
					mt9v022->fmts, mt9v022->num_fmts);
		mf->colorspace	= mt9v022->fmt->colorspace;
	}

	return ret;
}
