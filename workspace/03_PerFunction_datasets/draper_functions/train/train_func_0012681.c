s5k5baf_enum_frame_interval(struct v4l2_subdev *sd,
			      struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_frame_interval_enum *fie)
{
	if (fie->index > S5K5BAF_MAX_FR_TIME - S5K5BAF_MIN_FR_TIME ||
	    fie->pad != PAD_CIS)
		return -EINVAL;

	v4l_bound_align_image(&fie->width, S5K5BAF_WIN_WIDTH_MIN,
			      S5K5BAF_CIS_WIDTH, 1,
			      &fie->height, S5K5BAF_WIN_HEIGHT_MIN,
			      S5K5BAF_CIS_HEIGHT, 1, 0);

	fie->interval.numerator = S5K5BAF_MIN_FR_TIME + fie->index;
	fie->interval.denominator = 10000;

	return 0;
}
