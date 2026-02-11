vidioc_g_fmt_vid_cap(struct file *file, void *_fh,
				struct v4l2_format *f)
{
	struct hdpvr_device *dev = video_drvdata(file);
	struct hdpvr_fh *fh = _fh;
	int ret;


	if (fh->legacy_mode) {
		struct hdpvr_video_info vid_info;

		ret = get_video_info(dev, &vid_info);
		if (ret < 0)
			return ret;
		if (!vid_info.valid)
			return -EFAULT;
		f->fmt.pix.width = vid_info.width;
		f->fmt.pix.height = vid_info.height;
	} else {
		f->fmt.pix.width = dev->width;
		f->fmt.pix.height = dev->height;
	}
	f->fmt.pix.pixelformat	= V4L2_PIX_FMT_MPEG;
	f->fmt.pix.sizeimage	= dev->bulk_in_size;
	f->fmt.pix.bytesperline	= 0;
	if (f->fmt.pix.width == 720) {

		f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
		f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else {

		f->fmt.pix.colorspace = V4L2_COLORSPACE_REC709;
		f->fmt.pix.field = V4L2_FIELD_NONE;
	}
	return 0;
}
