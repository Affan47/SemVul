ov2640_get_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *mf = &format->format;
	struct i2c_client  *client = v4l2_get_subdevdata(sd);
	struct ov2640_priv *priv = to_ov2640(client);

	if (format->pad)
		return -EINVAL;

	if (!priv->win) {
		u32 width = SVGA_WIDTH, height = SVGA_HEIGHT;
		priv->win = ov2640_select_win(&width, &height);
		priv->cfmt_code = MEDIA_BUS_FMT_UYVY8_2X8;
	}

	mf->width	= priv->win->width;
	mf->height	= priv->win->height;
	mf->code	= priv->cfmt_code;

	switch (mf->code) {
	case MEDIA_BUS_FMT_RGB565_2X8_BE:
	case MEDIA_BUS_FMT_RGB565_2X8_LE:
		mf->colorspace = V4L2_COLORSPACE_SRGB;
		break;
	default:
	case MEDIA_BUS_FMT_YUYV8_2X8:
	case MEDIA_BUS_FMT_UYVY8_2X8:
		mf->colorspace = V4L2_COLORSPACE_JPEG;
	}
	mf->field	= V4L2_FIELD_NONE;

	return 0;
}
