sh_vou_try_fmt_vid_out(struct file *file, void *priv,
				  struct v4l2_format *fmt)
{
	struct sh_vou_device *vou_dev = video_drvdata(file);
	struct v4l2_pix_format *pix = &fmt->fmt.pix;
	unsigned int img_height_max;
	int pix_idx;

	dev_dbg(vou_dev->v4l2_dev.dev, "%s()\n", __func__);

	pix->field = V4L2_FIELD_INTERLACED;
	pix->colorspace = V4L2_COLORSPACE_SMPTE170M;
	pix->ycbcr_enc = pix->quantization = 0;

	for (pix_idx = 0; pix_idx < ARRAY_SIZE(vou_fmt); pix_idx++)
		if (vou_fmt[pix_idx].pfmt == pix->pixelformat)
			break;

	if (pix_idx == ARRAY_SIZE(vou_fmt))
		return -EINVAL;

	if (vou_dev->std & V4L2_STD_525_60)
		img_height_max = 480;
	else
		img_height_max = 576;

	v4l_bound_align_image(&pix->width,
			      VOU_MIN_IMAGE_WIDTH, VOU_MAX_IMAGE_WIDTH, 2,
			      &pix->height,
			      VOU_MIN_IMAGE_HEIGHT, img_height_max, 1, 0);
	pix->bytesperline = pix->width * vou_fmt[pix_idx].bpl;
	pix->sizeimage = pix->height * ((pix->width * vou_fmt[pix_idx].bpp) >> 3);

	return 0;
}
