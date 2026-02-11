upd64083_s_routing(struct v4l2_subdev *sd,
			      u32 input, u32 output, u32 config)
{
	struct upd64083_state *state = to_state(sd);
	u8 r00, r02;

	if (input > 7 || (input & 6) == 6)
		return -EINVAL;
	state->mode = (input & 3) << 6;
	state->ext_y_adc = (input & UPD64083_EXT_Y_ADC) << 3;
	r00 = (state->regs[R00] & ~(3 << 6)) | state->mode;
	r02 = (state->regs[R02] & ~(1 << 5)) | state->ext_y_adc;
	upd64083_write(sd, R00, r00);
	upd64083_write(sd, R02, r02);
	return 0;
}
