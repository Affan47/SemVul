vidioc_g_fmt_vid_cap(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct au0828_dev *dev = video_drvdata(file);

	dprintk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	f->fmt.pix.width = dev->width;
	f->fmt.pix.height = dev->height;
	f->fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
	f->fmt.pix.bytesperline = dev->bytesperline;
	f->fmt.pix.sizeimage = dev->frame_size;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	f->fmt.pix.priv = 0;
	return 0;
}
