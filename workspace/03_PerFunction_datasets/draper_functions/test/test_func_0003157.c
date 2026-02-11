stk_try_fmt_vid_cap(struct file *filp,
		struct v4l2_format *fmtd, int *idx)
{
	int i;
	switch (fmtd->fmt.pix.pixelformat) {
	case V4L2_PIX_FMT_RGB565:
	case V4L2_PIX_FMT_RGB565X:
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_SBGGR8:
		break;
	default:
		return -EINVAL;
	}
	for (i = 1; i < ARRAY_SIZE(stk_sizes); i++) {
		if (fmtd->fmt.pix.width > stk_sizes[i].w)
			break;
	}
	if (i == ARRAY_SIZE(stk_sizes)
		|| (abs(fmtd->fmt.pix.width - stk_sizes[i-1].w)
			< abs(fmtd->fmt.pix.width - stk_sizes[i].w))) {
		fmtd->fmt.pix.height = stk_sizes[i-1].h;
		fmtd->fmt.pix.width = stk_sizes[i-1].w;
		if (idx)
			*idx = i - 1;
	} else {
		fmtd->fmt.pix.height = stk_sizes[i].h;
		fmtd->fmt.pix.width = stk_sizes[i].w;
		if (idx)
			*idx = i;
	}

	fmtd->fmt.pix.field = V4L2_FIELD_NONE;
	fmtd->fmt.pix.colorspace = V4L2_COLORSPACE_SRGB;
	if (fmtd->fmt.pix.pixelformat == V4L2_PIX_FMT_SBGGR8)
		fmtd->fmt.pix.bytesperline = fmtd->fmt.pix.width;
	else
		fmtd->fmt.pix.bytesperline = 2 * fmtd->fmt.pix.width;
	fmtd->fmt.pix.sizeimage = fmtd->fmt.pix.bytesperline
		* fmtd->fmt.pix.height;
	return 0;
}
