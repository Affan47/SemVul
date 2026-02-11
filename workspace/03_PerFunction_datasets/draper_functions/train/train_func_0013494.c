cx18_av_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct cx18 *cx = v4l2_get_subdevdata(sd);

	CX18_DEBUG_INFO_DEV(sd, "%s output\n", enable ? "enable" : "disable");
	if (enable) {
		cx18_av_write(cx, 0x115, 0x8c);
		cx18_av_write(cx, 0x116, 0x07);
	} else {
		cx18_av_write(cx, 0x115, 0x00);
		cx18_av_write(cx, 0x116, 0x00);
	}
	return 0;
}
