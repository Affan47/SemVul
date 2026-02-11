vivid_vid_cap_g_selection(struct file *file, void *priv,
			      struct v4l2_selection *sel)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (!dev->has_crop_cap && !dev->has_compose_cap)
		return -ENOTTY;
	if (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	if (vivid_is_webcam(dev))
		return -EINVAL;

	sel->r.left = sel->r.top = 0;
	switch (sel->target) {
	case V4L2_SEL_TGT_CROP:
		if (!dev->has_crop_cap)
			return -EINVAL;
		sel->r = dev->crop_cap;
		break;
	case V4L2_SEL_TGT_CROP_DEFAULT:
	case V4L2_SEL_TGT_CROP_BOUNDS:
		if (!dev->has_crop_cap)
			return -EINVAL;
		sel->r = dev->src_rect;
		break;
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
		if (!dev->has_compose_cap)
			return -EINVAL;
		sel->r = vivid_max_rect;
		break;
	case V4L2_SEL_TGT_COMPOSE:
		if (!dev->has_compose_cap)
			return -EINVAL;
		sel->r = dev->compose_cap;
		break;
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
		if (!dev->has_compose_cap)
			return -EINVAL;
		sel->r = dev->fmt_cap_rect;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}
