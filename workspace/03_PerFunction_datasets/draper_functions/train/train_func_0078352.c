stv0299_set_frontend(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct stv0299_state* state = fe->demodulator_priv;
	int invval = 0;

	dprintk ("%s : FE_SET_FRONTEND\n", __func__);
	if (state->config->set_ts_params)
		state->config->set_ts_params(fe, 0);


	if (p->inversion == INVERSION_OFF) invval = 0;
	else if (p->inversion == INVERSION_ON) invval = 1;
	else {
		printk("stv0299 does not support auto-inversion\n");
		return -EINVAL;
	}
	if (state->config->invert) invval = (~invval) & 1;
	stv0299_writeregI(state, 0x0c, (stv0299_readreg(state, 0x0c) & 0xfe) | invval);

	if (fe->ops.tuner_ops.set_params) {
		fe->ops.tuner_ops.set_params(fe);
		if (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	}

	stv0299_set_FEC(state, p->fec_inner);
	stv0299_set_symbolrate(fe, p->symbol_rate);
	stv0299_writeregI(state, 0x22, 0x00);
	stv0299_writeregI(state, 0x23, 0x00);

	state->tuner_frequency = p->frequency;
	state->fec_inner = p->fec_inner;
	state->symbol_rate = p->symbol_rate;

	return 0;
}
