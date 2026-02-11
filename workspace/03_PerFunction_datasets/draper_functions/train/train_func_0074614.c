cx24123_set_voltage(struct dvb_frontend *fe,
			       enum fe_sec_voltage voltage)
{
	struct cx24123_state *state = fe->demodulator_priv;
	u8 val;

	val = cx24123_readreg(state, 0x29) & ~0x40;

	switch (voltage) {
	case SEC_VOLTAGE_13:
		dprintk("setting voltage 13V\n");
		return cx24123_writereg(state, 0x29, val & 0x7f);
	case SEC_VOLTAGE_18:
		dprintk("setting voltage 18V\n");
		return cx24123_writereg(state, 0x29, val | 0x80);
	case SEC_VOLTAGE_OFF:

		return 0;
	default:
		return -EINVAL;
	}

	return 0;
}
