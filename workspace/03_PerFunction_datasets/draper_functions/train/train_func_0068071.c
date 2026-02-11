s5k5baf_enum_mbus_code(struct v4l2_subdev *sd,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_mbus_code_enum *code)
{
	if (code->pad == PAD_CIS) {
		if (code->index > 0)
			return -EINVAL;
		code->code = MEDIA_BUS_FMT_FIXED;
		return 0;
	}

	if (code->index >= ARRAY_SIZE(s5k5baf_formats))
		return -EINVAL;

	code->code = s5k5baf_formats[code->index].code;
	return 0;
}
