sp8870_set_frontend_parameters(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct sp8870_state* state = fe->demodulator_priv;
	int  err;
	u16 reg0xc05;

	if ((err = configure_reg0xc05(p, &reg0xc05)))
		return err;


	sp8870_microcontroller_stop(state);


	if (fe->ops.tuner_ops.set_params) {
		fe->ops.tuner_ops.set_params(fe);
		if (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	}


	sp8870_writereg(state, 0x0319, 0x000A);


	sp8870_writereg(state, 0x031A, 0x0AAB);


	sp8870_writereg(state, 0x0309, 0x0400);


	sp8870_writereg(state, 0x030A, 0x0000);


	if (p->bandwidth_hz == 6000000)
		sp8870_writereg(state, 0x0311, 0x0002);
	else if (p->bandwidth_hz == 7000000)
		sp8870_writereg(state, 0x0311, 0x0001);
	else
		sp8870_writereg(state, 0x0311, 0x0000);


	if (p->transmission_mode == TRANSMISSION_MODE_2K)
		sp8870_writereg(state, 0x0338, 0x0000);
	else
		sp8870_writereg(state, 0x0338, 0x0001);

	sp8870_writereg(state, 0xc05, reg0xc05);


	sp8870_readreg(state, 0x200);


	sp8870_microcontroller_start(state);

	return 0;
}
