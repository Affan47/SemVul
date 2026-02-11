adv7842_get_format(struct v4l2_subdev *sd,
			      struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_format *format)
{
	struct adv7842_state *state = to_state(sd);

	if (format->pad != ADV7842_PAD_SOURCE)
		return -EINVAL;

	if (state->mode == ADV7842_MODE_SDP) {

		if (!(sdp_read(sd, 0x5a) & 0x01))
			return -EINVAL;
		format->format.code = MEDIA_BUS_FMT_YUYV8_2X8;
		format->format.width = 720;

		if (state->norm & V4L2_STD_525_60)
			format->format.height = 480;
		else
			format->format.height = 576;
		format->format.colorspace = V4L2_COLORSPACE_SMPTE170M;
		return 0;
	}

	adv7842_fill_format(state, &format->format);

	if (format->which == V4L2_SUBDEV_FORMAT_TRY) {
		struct v4l2_mbus_framefmt *fmt;

		fmt = v4l2_subdev_get_try_format(sd, cfg, format->pad);
		format->format.code = fmt->code;
	} else {
		format->format.code = state->format->code;
	}

	return 0;
}
