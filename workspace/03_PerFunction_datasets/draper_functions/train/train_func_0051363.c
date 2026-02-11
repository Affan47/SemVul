sr030pc30_enum_mbus_code(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_mbus_code_enum *code)
{
	if (!code || code->pad ||
	    code->index >= ARRAY_SIZE(sr030pc30_formats))
		return -EINVAL;

	code->code = sr030pc30_formats[code->index].code;
	return 0;
}
