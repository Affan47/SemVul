mxr_get_mbus_fmt(struct mxr_device *mdev,
	struct v4l2_mbus_framefmt *mbus_fmt)
{
	struct v4l2_subdev *sd;
	struct v4l2_subdev_format fmt = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret;

	mutex_lock(&mdev->mutex);
	sd = to_outsd(mdev);
	ret = v4l2_subdev_call(sd, pad, get_fmt, NULL, &fmt);
	*mbus_fmt = fmt.format;
	WARN(ret, "failed to get mbus_fmt for output %s\n", sd->name);
	mutex_unlock(&mdev->mutex);
}
