ves1820_setup_reg0(struct ves1820_state *state,
			      u8 reg0, enum fe_spectral_inversion inversion)
{
	reg0 |= state->reg0 & 0x62;

	if (INVERSION_ON == inversion) {
		if (!state->config->invert) reg0 |= 0x20;
		else reg0 &= ~0x20;
	} else if (INVERSION_OFF == inversion) {
		if (!state->config->invert) reg0 &= ~0x20;
		else reg0 |= 0x20;
	}

	ves1820_writereg(state, 0x00, reg0 & 0xfe);
	ves1820_writereg(state, 0x00, reg0 | 0x01);

	state->reg0 = reg0;

	return 0;
}
