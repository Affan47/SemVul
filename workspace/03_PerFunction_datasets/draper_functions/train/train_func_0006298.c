v4l_g_crop(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct v4l2_crop *p = arg;
	struct v4l2_selection s = {
		.type = p->type,
	};
	int ret;

	if (ops->vidioc_g_crop)
		return ops->vidioc_g_crop(file, fh, p);


	if (V4L2_TYPE_IS_OUTPUT(p->type))
		s.target = V4L2_SEL_TGT_COMPOSE_ACTIVE;
	else
		s.target = V4L2_SEL_TGT_CROP_ACTIVE;

	ret = ops->vidioc_g_selection(file, fh, &s);


	if (!ret)
		p->c = s.r;
	return ret;
}
