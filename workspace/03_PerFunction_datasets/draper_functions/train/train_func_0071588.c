overlay_get(int fd)
{
	if (options[OptGetOverlayFormat]) {
		struct v4l2_format fmt;

		fmt.type = V4L2_BUF_TYPE_VIDEO_OVERLAY;
		if (doioctl(fd, VIDIOC_G_FMT, &fmt) == 0)
			printfmt(fmt);
	}

	if (options[OptGetOutputOverlayFormat]) {
		struct v4l2_format fmt;

		fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY;
		if (doioctl(fd, VIDIOC_G_FMT, &fmt) == 0)
			printfmt(fmt);
	}

	if (options[OptGetFBuf]) {
		struct v4l2_framebuffer fb;
		if (doioctl(fd, VIDIOC_G_FBUF, &fb) == 0)
			printfbuf(fb);
	}
}
