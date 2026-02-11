tw9910_get_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *mf = &format->format;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct tw9910_priv *priv = to_tw9910(client);

	if (format->pad)
		return -EINVAL;

	if (!priv->scale) {
		priv->scale = tw9910_select_norm(priv->norm, 640, 480);
		if (!priv->scale)
			return -EINVAL;
	}

	mf->width	= priv->scale->width;
	mf->height	= priv->scale->height;
	mf->code	= MEDIA_BUS_FMT_UYVY8_2X8;
	mf->colorspace	= V4L2_COLORSPACE_SMPTE170M;
	mf->field	= V4L2_FIELD_INTERLACED_BT;

	return 0;
}
