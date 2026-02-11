tvp5150_s_crop(struct v4l2_subdev *sd, const struct v4l2_crop *a)
{
	struct v4l2_rect rect = a->c;
	struct tvp5150 *decoder = to_tvp5150(sd);
	v4l2_std_id std;
	unsigned int hmax;

	v4l2_dbg(1, debug, sd, "%s left=%d, top=%d, width=%d, height=%d\n",
		__func__, rect.left, rect.top, rect.width, rect.height);

	if (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;


	rect.left = clamp(rect.left, 0, TVP5150_MAX_CROP_LEFT);
	rect.width = clamp_t(unsigned int, rect.width,
			     TVP5150_H_MAX - TVP5150_MAX_CROP_LEFT - rect.left,
			     TVP5150_H_MAX - rect.left);
	rect.top = clamp(rect.top, 0, TVP5150_MAX_CROP_TOP);


	if (decoder->norm == V4L2_STD_ALL)
		std = tvp5150_read_std(sd);
	else
		std = decoder->norm;

	if (std & V4L2_STD_525_60)
		hmax = TVP5150_V_MAX_525_60;
	else
		hmax = TVP5150_V_MAX_OTHERS;

	rect.height = clamp_t(unsigned int, rect.height,
			      hmax - TVP5150_MAX_CROP_TOP - rect.top,
			      hmax - rect.top);

	tvp5150_write(sd, TVP5150_VERT_BLANKING_START, rect.top);
	tvp5150_write(sd, TVP5150_VERT_BLANKING_STOP,
		      rect.top + rect.height - hmax);
	tvp5150_write(sd, TVP5150_ACT_VD_CROP_ST_MSB,
		      rect.left >> TVP5150_CROP_SHIFT);
	tvp5150_write(sd, TVP5150_ACT_VD_CROP_ST_LSB,
		      rect.left | (1 << TVP5150_CROP_SHIFT));
	tvp5150_write(sd, TVP5150_ACT_VD_CROP_STP_MSB,
		      (rect.left + rect.width - TVP5150_MAX_CROP_LEFT) >>
		      TVP5150_CROP_SHIFT);
	tvp5150_write(sd, TVP5150_ACT_VD_CROP_STP_LSB,
		      rect.left + rect.width - TVP5150_MAX_CROP_LEFT);

	decoder->rect = rect;

	return 0;
}
