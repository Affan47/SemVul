mx2_camera_try_fmt(struct soc_camera_device *icd,
				  struct v4l2_format *f)
{
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	const struct soc_camera_format_xlate *xlate;
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct v4l2_subdev_pad_config pad_cfg;
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_TRY,
	};
	struct v4l2_mbus_framefmt *mf = &format.format;
	__u32 pixfmt = pix->pixelformat;
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct mx2_camera_dev *pcdev = ici->priv;
	struct mx2_fmt_cfg *emma_prp;
	int ret;

	dev_dbg(icd->parent, "%s: requested params: width = %d, height = %d\n",
		__func__, pix->width, pix->height);

	xlate = soc_camera_xlate_by_fourcc(icd, pixfmt);
	if (pixfmt && !xlate) {
		dev_warn(icd->parent, "Format %x not found\n", pixfmt);
		return -EINVAL;
	}


	pix->width &= ~0x7;


	mf->width	= pix->width;
	mf->height	= pix->height;
	mf->field	= pix->field;
	mf->colorspace	= pix->colorspace;
	mf->code	= xlate->code;

	ret = v4l2_subdev_call(sd, pad, set_fmt, &pad_cfg, &format);
	if (ret < 0)
		return ret;

	dev_dbg(icd->parent, "%s: sensor params: width = %d, height = %d\n",
		__func__, pcdev->s_width, pcdev->s_height);


	emma_prp = mx27_emma_prp_get_format(xlate->code,
					    xlate->host_fmt->fourcc);

	if ((mf->width != pix->width || mf->height != pix->height) &&
		emma_prp->cfg.in_fmt == PRP_CNTL_DATA_IN_YUV422) {
		if (mx2_emmaprp_resize(pcdev, mf, pix, false) < 0)
			dev_dbg(icd->parent, "%s: can't resize\n", __func__);
	}

	if (mf->field == V4L2_FIELD_ANY)
		mf->field = V4L2_FIELD_NONE;


	if (mf->field != V4L2_FIELD_NONE && !V4L2_FIELD_HAS_BOTH(mf->field)) {
		dev_err(icd->parent, "Field type %d unsupported.\n",
				mf->field);
		return -EINVAL;
	}

	pix->width	= mf->width;
	pix->height	= mf->height;
	pix->field	= mf->field;
	pix->colorspace	= mf->colorspace;

	dev_dbg(icd->parent, "%s: returned params: width = %d, height = %d\n",
		__func__, pix->width, pix->height);

	return 0;
}
