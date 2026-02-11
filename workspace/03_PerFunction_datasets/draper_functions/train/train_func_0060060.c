mt9v032_set_format(struct v4l2_subdev *subdev,
			      struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_format *format)
{
	struct mt9v032 *mt9v032 = to_mt9v032(subdev);
	struct v4l2_mbus_framefmt *__format;
	struct v4l2_rect *__crop;
	unsigned int width;
	unsigned int height;
	unsigned int hratio;
	unsigned int vratio;

	__crop = __mt9v032_get_pad_crop(mt9v032, cfg, format->pad,
					format->which);


	width = clamp(ALIGN(format->format.width, 2),
		      max_t(unsigned int, __crop->width / 4,
			    MT9V032_WINDOW_WIDTH_MIN),
		      __crop->width);
	height = clamp(ALIGN(format->format.height, 2),
		       max_t(unsigned int, __crop->height / 4,
			     MT9V032_WINDOW_HEIGHT_MIN),
		       __crop->height);

	hratio = mt9v032_calc_ratio(__crop->width, width);
	vratio = mt9v032_calc_ratio(__crop->height, height);

	__format = __mt9v032_get_pad_format(mt9v032, cfg, format->pad,
					    format->which);
	__format->width = __crop->width / hratio;
	__format->height = __crop->height / vratio;

	if (format->which == V4L2_SUBDEV_FORMAT_ACTIVE) {
		mt9v032->hratio = hratio;
		mt9v032->vratio = vratio;
		mt9v032_configure_pixel_rate(mt9v032);
	}

	format->format = *__format;

	return 0;
}
