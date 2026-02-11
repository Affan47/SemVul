stv0367ter_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct stv0367_state *state = fe->demodulator_priv;
	u8 tmp = stv0367_readreg(state, R367TER_I2CRPT);

	dprintk("%s:\n", __func__);

	if (enable) {
		stv0367_setbits(&tmp, F367TER_STOP_ENABLE, 0);
		stv0367_setbits(&tmp, F367TER_I2CT_ON, 1);
	} else {
		stv0367_setbits(&tmp, F367TER_STOP_ENABLE, 1);
		stv0367_setbits(&tmp, F367TER_I2CT_ON, 0);
	}

	stv0367_writereg(state, R367TER_I2CRPT, tmp);

	return 0;
}
