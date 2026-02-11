vpfe_enum_size(struct file *file, void  *priv,
			  struct v4l2_frmsizeenum *fsize)
{
	struct vpfe_device *vpfe = video_drvdata(file);
	struct v4l2_subdev_frame_size_enum fse;
	struct vpfe_subdev_info *sdinfo;
	struct v4l2_mbus_framefmt mbus;
	struct v4l2_pix_format pix;
	struct vpfe_fmt *fmt;
	int ret;

	vpfe_dbg(2, vpfe, "vpfe_enum_size\n");


	fmt = find_format_by_pix(fsize->pixel_format);
	if (!fmt) {
		vpfe_dbg(3, vpfe, "Invalid pixel code: %x, default used instead\n",
			fsize->pixel_format);
		return -EINVAL;
	}

	memset(fsize->reserved, 0x0, sizeof(fsize->reserved));

	sdinfo = vpfe->current_subdev;
	if (!sdinfo->sd)
		return -EINVAL;

	memset(&pix, 0x0, sizeof(pix));

	pix.pixelformat = fsize->pixel_format;
	pix.width = 640;
	pix.height = 480;
	pix.colorspace = V4L2_COLORSPACE_SRGB;
	pix.field = V4L2_FIELD_NONE;
	pix_to_mbus(vpfe, &pix, &mbus);

	memset(&fse, 0x0, sizeof(fse));
	fse.index = fsize->index;
	fse.pad = 0;
	fse.code = mbus.code;
	fse.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(sdinfo->sd, pad, enum_frame_size, NULL, &fse);
	if (ret)
		return -EINVAL;

	vpfe_dbg(1, vpfe, "vpfe_enum_size: index: %d code: %x W:[%d,%d] H:[%d,%d]\n",
		fse.index, fse.code, fse.min_width, fse.max_width,
		fse.min_height, fse.max_height);

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = fse.max_width;
	fsize->discrete.height = fse.max_height;

	vpfe_dbg(1, vpfe, "vpfe_enum_size: index: %d pixformat: %s size: %dx%d\n",
		fsize->index, print_fourcc(fsize->pixel_format),
		fsize->discrete.width, fsize->discrete.height);

	return 0;
}
