lg2160_agc_fix(struct lg216x_state *state,
			  int if_agc_fix, int rf_agc_fix)
{
	u8 val;
	int ret;

	ret = lg216x_read_reg(state, 0x0100, &val);
	if (lg_fail(ret))
		goto fail;

	val &= 0xf3;
	val |= (if_agc_fix) ? 0x08 : 0x00;
	val |= (rf_agc_fix) ? 0x04 : 0x00;

	ret = lg216x_write_reg(state, 0x0100, val);
	lg_fail(ret);
fail:
	return ret;
}
