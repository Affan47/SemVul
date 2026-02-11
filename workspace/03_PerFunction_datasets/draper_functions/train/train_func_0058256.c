smiapp_set_format_source(struct v4l2_subdev *subdev,
				    struct v4l2_subdev_pad_config *cfg,
				    struct v4l2_subdev_format *fmt)
{
	struct smiapp_sensor *sensor = to_smiapp_sensor(subdev);
	const struct smiapp_csi_data_format *csi_format,
		*old_csi_format = sensor->csi_format;
	unsigned long *valid_link_freqs;
	u32 code = fmt->format.code;
	unsigned int i;
	int rval;

	rval = __smiapp_get_format(subdev, cfg, fmt);
	if (rval)
		return rval;


	if (subdev != &sensor->src->sd)
		return 0;

	csi_format = smiapp_validate_csi_data_format(sensor, code);

	fmt->format.code = csi_format->code;

	if (fmt->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		return 0;

	sensor->csi_format = csi_format;

	if (csi_format->width != old_csi_format->width)
		for (i = 0; i < ARRAY_SIZE(sensor->test_data); i++)
			__v4l2_ctrl_modify_range(
				sensor->test_data[i], 0,
				(1 << csi_format->width) - 1, 1, 0);

	if (csi_format->compressed == old_csi_format->compressed)
		return 0;

	valid_link_freqs =
		&sensor->valid_link_freqs[sensor->csi_format->compressed
					  - SMIAPP_COMPRESSED_BASE];

	__v4l2_ctrl_modify_range(
		sensor->link_freq, 0,
		__fls(*valid_link_freqs), ~*valid_link_freqs,
		__ffs(*valid_link_freqs));

	return smiapp_pll_update(sensor);
}
