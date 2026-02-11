stv0297_read_signal_strength(struct dvb_frontend *fe, u16 * strength)
{
	struct stv0297_state *state = fe->demodulator_priv;
	u8 STRENGTH[3];
	u16 tmp;

	stv0297_readregs(state, 0x41, STRENGTH, 3);
	tmp = (STRENGTH[1] & 0x03) << 8 | STRENGTH[0];
	if (STRENGTH[2] & 0x20) {
		if (tmp < 0x200)
			tmp = 0;
		else
			tmp = tmp - 0x200;
	} else {
		if (tmp > 0x1ff)
			tmp = 0;
		else
			tmp = 0x1ff - tmp;
	}
	*strength = (tmp << 7) | (tmp >> 2);
	return 0;
}
