saa711x_g_input_status(struct v4l2_subdev *sd, u32 *status)
{
	struct saa711x_state *state = to_state(sd);
	int reg1e = 0x80;
	int reg1f;

	*status = V4L2_IN_ST_NO_SIGNAL;
	if (state->ident == SAA7115)
		reg1e = saa711x_read(sd, R_1E_STATUS_BYTE_1_VD_DEC);
	reg1f = saa711x_read(sd, R_1F_STATUS_BYTE_2_VD_DEC);
	if ((reg1f & 0xc1) == 0x81 && (reg1e & 0xc0) == 0x80)
		*status = 0;
	return 0;
}
