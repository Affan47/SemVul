ks0127_s_stream(struct v4l2_subdev *sd, int enable)
{
	v4l2_dbg(1, debug, sd, "s_stream(%d)\n", enable);
	if (enable) {

		ks0127_and_or(sd, KS_OFMTA, 0xcf, 0x30);

		ks0127_and_or(sd, KS_CDEM, 0x7f, 0x00);
	} else {

		ks0127_and_or(sd, KS_OFMTA, 0xcf, 0x00);

		ks0127_and_or(sd, KS_CDEM, 0x7f, 0x80);
	}
	return 0;
}
