ov2659_get_fmt(struct v4l2_subdev *sd,
			  struct v4l2_subdev_pad_config *cfg,
			  struct v4l2_subdev_format *fmt)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ov2659 *ov2659 = to_ov2659(sd);

	dev_dbg(&client->dev, "ov2659_get_fmt\n");

	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY) {
#ifdef CONFIG_VIDEO_V4L2_SUBDEV_API
		struct v4l2_mbus_framefmt *mf;

		mf = v4l2_subdev_get_try_format(sd, cfg, 0);
		mutex_lock(&ov2659->lock);
		fmt->format = *mf;
		mutex_unlock(&ov2659->lock);
		return 0;
#else
	return -ENOTTY;
#endif
	}

	mutex_lock(&ov2659->lock);
	fmt->format = ov2659->format;
	mutex_unlock(&ov2659->lock);

	dev_dbg(&client->dev, "ov2659_get_fmt: %x %dx%d\n",
		ov2659->format.code, ov2659->format.width,
		ov2659->format.height);

	return 0;
}
