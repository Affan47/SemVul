cx22700_set_frontend(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct cx22700_state* state = fe->demodulator_priv;

	cx22700_writereg (state, 0x00, 0x02);
	cx22700_writereg (state, 0x00, 0x00);

	if (fe->ops.tuner_ops.set_params) {
		fe->ops.tuner_ops.set_params(fe);
		if (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	}

	cx22700_set_inversion(state, c->inversion);
	cx22700_set_tps(state, c);
	cx22700_writereg (state, 0x37, 0x01);
	cx22700_writereg (state, 0x00, 0x01);

	return 0;
}
