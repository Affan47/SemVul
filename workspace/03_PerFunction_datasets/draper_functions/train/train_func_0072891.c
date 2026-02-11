v4lconvert_fixup_fmt(struct v4l2_format *fmt)
{
	switch (fmt->fmt.pix.pixelformat) {
	case V4L2_PIX_FMT_RGB24:
	case V4L2_PIX_FMT_BGR24:
		fmt->fmt.pix.bytesperline = fmt->fmt.pix.width * 3;
		fmt->fmt.pix.sizeimage = fmt->fmt.pix.width * fmt->fmt.pix.height * 3;
		break;
	case V4L2_PIX_FMT_YUV420:
	case V4L2_PIX_FMT_YVU420:
		fmt->fmt.pix.bytesperline = fmt->fmt.pix.width;
		fmt->fmt.pix.sizeimage = fmt->fmt.pix.width * fmt->fmt.pix.height * 3 / 2;
		break;
	}
}
