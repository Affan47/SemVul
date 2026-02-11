mt9m032_update_timing(struct mt9m032 *sensor,
				 struct v4l2_fract *interval)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	struct v4l2_rect *crop = &sensor->crop;
	unsigned int min_vblank;
	unsigned int vblank;
	u32 row_time;

	if (!interval)
		interval = &sensor->frame_interval;

	row_time = mt9m032_row_time(sensor, crop->width);

	vblank = div_u64(1000000000ULL * interval->numerator,
			 (u64)row_time * interval->denominator)
	       - crop->height;

	if (vblank > MT9M032_VBLANK_MAX) {

		interval->denominator = 1000;
		interval->numerator =
			div_u64((crop->height + MT9M032_VBLANK_MAX) *
				(u64)row_time * interval->denominator,
				1000000000ULL);
		vblank = div_u64(1000000000ULL * interval->numerator,
				 (u64)row_time * interval->denominator)
		       - crop->height;
	}

	min_vblank = 1600000 / row_time;
	vblank = clamp_t(unsigned int, vblank, min_vblank, MT9M032_VBLANK_MAX);

	return mt9m032_write(client, MT9M032_VBLANK, vblank);
}
