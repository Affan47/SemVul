vidioc_enum_fmt_vid_cap(struct file *file, void  *priv,
					struct v4l2_fmtdesc *fmt)
{
	char *desc = NULL;

	switch (fmt->index) {
	case 0:
		fmt->pixelformat = V4L2_PIX_FMT_MJPEG;
		desc = "Motion JPEG";
		break;
	case 1:
		fmt->pixelformat = V4L2_PIX_FMT_MPEG1;
		desc = "MPEG-1 ES";
		break;
	case 2:
		fmt->pixelformat = V4L2_PIX_FMT_MPEG2;
		desc = "MPEG-2 ES";
		break;
	case 3:
		fmt->pixelformat = V4L2_PIX_FMT_MPEG4;
		desc = "MPEG-4 ES";
		break;
	default:
		return -EINVAL;
	}
	fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt->flags = V4L2_FMT_FLAG_COMPRESSED;

	strncpy(fmt->description, desc, sizeof(fmt->description));

	return 0;
}
