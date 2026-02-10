rj54n1_get_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *mf = &format->format;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct rj54n1 *rj54n1 = to_rj54n1(client);

	if (format->pad)
		return -EINVAL;

	mf->code	= rj54n1->fmt->code;
	mf->colorspace	= rj54n1->fmt->colorspace;
	mf->field	= V4L2_FIELD_NONE;
	mf->width	= rj54n1->width;
	mf->height	= rj54n1->height;

	return 0;
}
