stk_vidioc_s_fmt_vid_cap(struct file *filp,
		void *priv, struct v4l2_format *fmtd)
{
	int ret;
	int idx;
	struct stk_camera *dev = video_drvdata(filp);

	if (dev == NULL)
		return -ENODEV;
	if (!is_present(dev))
		return -ENODEV;
	if (is_streaming(dev))
		return -EBUSY;
	if (dev->owner)
		return -EBUSY;
	ret = stk_try_fmt_vid_cap(filp, fmtd, &idx);
	if (ret)
		return ret;

	dev->vsettings.palette = fmtd->fmt.pix.pixelformat;
	stk_free_buffers(dev);
	dev->frame_size = fmtd->fmt.pix.sizeimage;
	dev->vsettings.mode = stk_sizes[idx].m;

	stk_initialise(dev);
	return stk_setup_format(dev);
}
