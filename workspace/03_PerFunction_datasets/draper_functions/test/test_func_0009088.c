tvp5150_g_register(struct v4l2_subdev *sd, struct v4l2_dbg_register *reg)
{
	int res;

	res = tvp5150_read(sd, reg->reg & 0xff);
	if (res < 0) {
		v4l2_err(sd, "%s: failed with error = %d\n", __func__, res);
		return res;
	}

	reg->val = res;
	reg->size = 1;
	return 0;
}
