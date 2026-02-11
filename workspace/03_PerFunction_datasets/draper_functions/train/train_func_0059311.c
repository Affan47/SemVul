tvp5150_set_vbi(struct v4l2_subdev *sd,
			const struct i2c_vbi_ram_value *regs,
			unsigned int type,u8 flags, int line,
			const int fields)
{
	struct tvp5150 *decoder = to_tvp5150(sd);
	v4l2_std_id std = decoder->norm;
	u8 reg;
	int pos=0;

	if (std == V4L2_STD_ALL) {
		v4l2_err(sd, "VBI can't be configured without knowing number of lines\n");
		return 0;
	} else if (std & V4L2_STD_625_50) {

		line += 3;
	}

	if (line<6||line>27)
		return 0;

	while (regs->reg != (u16)-1 ) {
		if ((type & regs->type.vbi_type) &&
		    (line>=regs->type.ini_line) &&
		    (line<=regs->type.end_line)) {
			type=regs->type.vbi_type;
			break;
		}

		regs++;
		pos++;
	}
	if (regs->reg == (u16)-1)
		return 0;

	type=pos | (flags & 0xf0);
	reg=((line-6)<<1)+TVP5150_LINE_MODE_INI;

	if (fields&1) {
		tvp5150_write(sd, reg, type);
	}

	if (fields&2) {
		tvp5150_write(sd, reg+1, type);
	}

	return type;
}
