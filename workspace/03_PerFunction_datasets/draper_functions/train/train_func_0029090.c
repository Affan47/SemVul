solo_try_fmt_cap(struct file *file, void *priv,
			    struct v4l2_format *f)
{
	struct solo_dev *solo_dev = video_drvdata(file);
	struct v4l2_pix_format *pix = &f->fmt.pix;
	int image_size = solo_image_size(solo_dev);

	if (pix->pixelformat != V4L2_PIX_FMT_UYVY)
		return -EINVAL;

	pix->width = solo_dev->video_hsize;
	pix->height = solo_vlines(solo_dev);
	pix->sizeimage = image_size;
	pix->field = V4L2_FIELD_INTERLACED;
	pix->pixelformat = V4L2_PIX_FMT_UYVY;
	pix->colorspace = V4L2_COLORSPACE_SMPTE170M;
	pix->priv = 0;
	return 0;
}
