stk1135_enum_framesizes(struct gspca_dev *gspca_dev,
			struct v4l2_frmsizeenum *fsize)
{
	if (fsize->index != 0 || fsize->pixel_format != V4L2_PIX_FMT_SBGGR8)
		return -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	fsize->stepwise.min_width = 32;
	fsize->stepwise.min_height = 32;
	fsize->stepwise.max_width = 1280;
	fsize->stepwise.max_height = 1024;
	fsize->stepwise.step_width = 2;
	fsize->stepwise.step_height = 2;

	return 0;
}
