s5h1411_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct s5h1411_state *state = fe->demodulator_priv;
	u16 reg;
	dprintk("%s()\n", __func__);

	switch (state->current_modulation) {
	case QAM_64:
		reg = s5h1411_readreg(state, S5H1411_I2C_TOP_ADDR, 0xf1);
		return s5h1411_qam64_lookup_snr(fe, snr, reg);
	case QAM_256:
		reg = s5h1411_readreg(state, S5H1411_I2C_TOP_ADDR, 0xf1);
		return s5h1411_qam256_lookup_snr(fe, snr, reg);
	case VSB_8:
		reg = s5h1411_readreg(state, S5H1411_I2C_TOP_ADDR,
			0xf2) & 0x3ff;
		return s5h1411_vsb_lookup_snr(fe, snr, reg);
	default:
		break;
	}

	return -EINVAL;
}
