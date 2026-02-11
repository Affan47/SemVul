sh_vou_g_fmt_vid_out(struct file *file, void *priv,
				struct v4l2_format *fmt)
{
	struct sh_vou_device *vou_dev = video_drvdata(file);

	dev_dbg(vou_dev->v4l2_dev.dev, "%s()\n", __func__);

	fmt->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	fmt->fmt.pix = vou_dev->pix;

	return 0;
}
