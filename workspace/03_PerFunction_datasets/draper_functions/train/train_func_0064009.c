stk_vidioc_enum_framesizes(struct file *filp,
		void *priv, struct v4l2_frmsizeenum *frms)
{
	if (frms->index >= ARRAY_SIZE(stk_sizes))
		return -EINVAL;
	switch (frms->pixel_format) {
	case V4L2_PIX_FMT_RGB565:
	case V4L2_PIX_FMT_RGB565X:
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_SBGGR8:
		frms->type = V4L2_FRMSIZE_TYPE_DISCRETE;
		frms->discrete.width = stk_sizes[frms->index].w;
		frms->discrete.height = stk_sizes[frms->index].h;
		return 0;
	default: return -EINVAL;
	}
}
