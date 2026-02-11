ov6650_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *mf = &format->format;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ov6650 *priv = to_ov6650(client);

	if (format->pad)
		return -EINVAL;

	if (is_unscaled_ok(mf->width, mf->height, &priv->rect))
		v4l_bound_align_image(&mf->width, 2, W_CIF, 1,
				&mf->height, 2, H_CIF, 1, 0);

	mf->field = V4L2_FIELD_NONE;

	switch (mf->code) {
	case MEDIA_BUS_FMT_Y10_1X10:
		mf->code = MEDIA_BUS_FMT_Y8_1X8;
	case MEDIA_BUS_FMT_Y8_1X8:
	case MEDIA_BUS_FMT_YVYU8_2X8:
	case MEDIA_BUS_FMT_YUYV8_2X8:
	case MEDIA_BUS_FMT_VYUY8_2X8:
	case MEDIA_BUS_FMT_UYVY8_2X8:
		mf->colorspace = V4L2_COLORSPACE_JPEG;
		break;
	default:
		mf->code = MEDIA_BUS_FMT_SBGGR8_1X8;
	case MEDIA_BUS_FMT_SBGGR8_1X8:
		mf->colorspace = V4L2_COLORSPACE_SRGB;
		break;
	}

	if (format->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		return ov6650_s_fmt(sd, mf);
	cfg->try_fmt = *mf;

	return 0;
}
