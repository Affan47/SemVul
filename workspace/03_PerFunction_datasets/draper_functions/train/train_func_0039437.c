msi2500_s_fmt_sdr_cap(struct file *file, void *priv,
				 struct v4l2_format *f)
{
	struct msi2500_dev *dev = video_drvdata(file);
	struct vb2_queue *q = &dev->vb_queue;
	int i;

	dev_dbg(dev->dev, "pixelformat fourcc %4.4s\n",
		(char *)&f->fmt.sdr.pixelformat);

	if (vb2_is_busy(q))
		return -EBUSY;

	memset(f->fmt.sdr.reserved, 0, sizeof(f->fmt.sdr.reserved));
	for (i = 0; i < dev->num_formats; i++) {
		if (formats[i].pixelformat == f->fmt.sdr.pixelformat) {
			dev->pixelformat = formats[i].pixelformat;
			dev->buffersize = formats[i].buffersize;
			f->fmt.sdr.buffersize = formats[i].buffersize;
			return 0;
		}
	}

	dev->pixelformat = formats[0].pixelformat;
	dev->buffersize = formats[0].buffersize;
	f->fmt.sdr.pixelformat = formats[0].pixelformat;
	f->fmt.sdr.buffersize = formats[0].buffersize;

	return 0;
}
