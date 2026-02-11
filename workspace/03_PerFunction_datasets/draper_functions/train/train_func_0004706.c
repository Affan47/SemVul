sh_vou_s_selection(struct file *file, void *fh,
			      struct v4l2_selection *sel)
{
	struct v4l2_rect *rect = &sel->r;
	struct sh_vou_device *vou_dev = video_drvdata(file);
	struct v4l2_crop sd_crop = {.type = V4L2_BUF_TYPE_VIDEO_OUTPUT};
	struct v4l2_pix_format *pix = &vou_dev->pix;
	struct sh_vou_geometry geo;
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,

		.format.code = MEDIA_BUS_FMT_YUYV8_2X8,
		.format.field = V4L2_FIELD_INTERLACED,
		.format.colorspace = V4L2_COLORSPACE_SMPTE170M,
	};
	unsigned int img_height_max;
	int ret;

	if (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT ||
	    sel->target != V4L2_SEL_TGT_COMPOSE)
		return -EINVAL;

	if (vb2_is_busy(&vou_dev->queue))
		return -EBUSY;

	if (vou_dev->std & V4L2_STD_525_60)
		img_height_max = 480;
	else
		img_height_max = 576;

	v4l_bound_align_image(&rect->width,
			      VOU_MIN_IMAGE_WIDTH, VOU_MAX_IMAGE_WIDTH, 1,
			      &rect->height,
			      VOU_MIN_IMAGE_HEIGHT, img_height_max, 1, 0);

	if (rect->width + rect->left > VOU_MAX_IMAGE_WIDTH)
		rect->left = VOU_MAX_IMAGE_WIDTH - rect->width;

	if (rect->height + rect->top > img_height_max)
		rect->top = img_height_max - rect->height;

	geo.output = *rect;
	geo.in_width = pix->width;
	geo.in_height = pix->height;


	sd_crop.c.width = geo.output.width;
	sd_crop.c.height = geo.output.height;


	v4l2_device_call_until_err(&vou_dev->v4l2_dev, 0, video,
				   s_crop, &sd_crop);
	format.format.width = geo.output.width;
	format.format.height = geo.output.height;
	ret = v4l2_device_call_until_err(&vou_dev->v4l2_dev, 0, pad,
					 set_fmt, NULL, &format);

	if (ret < 0)
		return ret;


	if ((unsigned)format.format.width > VOU_MAX_IMAGE_WIDTH ||
	    (unsigned)format.format.height > img_height_max ||
	    format.format.code != MEDIA_BUS_FMT_YUYV8_2X8)
		return -EIO;

	geo.output.width = format.format.width;
	geo.output.height = format.format.height;


	vou_adjust_input(&geo, vou_dev->std);


	vou_dev->rect = geo.output;
	pix->width = geo.in_width;
	pix->height = geo.in_height;

	sh_vou_configure_geometry(vou_dev, vou_dev->pix_idx,
				  geo.scale_idx_h, geo.scale_idx_v);

	return 0;
}
