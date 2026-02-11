si2165_set_if_freq_shift(struct si2165_state *state, u32 IF)
{
	u64 if_freq_shift;
	s32 reg_value = 0;
	u32 fe_clk = si2165_get_fe_clk(state);

	if_freq_shift = IF;
	if_freq_shift <<= 29;

	do_div(if_freq_shift, fe_clk);
	reg_value = (s32)if_freq_shift;

	if (state->config.inversion)
		reg_value = -reg_value;

	reg_value = reg_value & 0x1fffffff;


	return si2165_writereg32(state, 0x00e8, reg_value);
}
