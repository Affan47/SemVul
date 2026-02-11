mt9p031_enum_frame_size(struct v4l2_subdev *subdev,
				   struct v4l2_subdev_pad_config *cfg,
				   struct v4l2_subdev_frame_size_enum *fse)
{
	struct mt9p031 *mt9p031 = to_mt9p031(subdev);

	if (fse->index >= 8 || fse->code != mt9p031->format.code)
		return -EINVAL;

	fse->min_width = MT9P031_WINDOW_WIDTH_DEF
		       / min_t(unsigned int, 7, fse->index + 1);
	fse->max_width = fse->min_width;
	fse->min_height = MT9P031_WINDOW_HEIGHT_DEF / (fse->index + 1);
	fse->max_height = fse->min_height;

	return 0;
}
