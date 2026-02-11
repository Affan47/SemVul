au8522_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct au8522_state *state = fe->demodulator_priv;
	u8 reg;
	u32 tuner_status = 0;

	*status = 0;

	if (state->current_modulation == VSB_8) {
		dprintk("%s() Checking VSB_8\n", __func__);
		reg = au8522_readreg(state, 0x4088);
		if ((reg & 0x03) == 0x03)
			*status |= FE_HAS_LOCK | FE_HAS_SYNC | FE_HAS_VITERBI;
	} else {
		dprintk("%s() Checking QAM\n", __func__);
		reg = au8522_readreg(state, 0x4541);
		if (reg & 0x80)
			*status |= FE_HAS_VITERBI;
		if (reg & 0x20)
			*status |= FE_HAS_LOCK | FE_HAS_SYNC;
	}

	switch (state->config->status_mode) {
	case AU8522_DEMODLOCKING:
		dprintk("%s() DEMODLOCKING\n", __func__);
		if (*status & FE_HAS_VITERBI)
			*status |= FE_HAS_CARRIER | FE_HAS_SIGNAL;
		break;
	case AU8522_TUNERLOCKING:

		dprintk("%s() TUNERLOCKING\n", __func__);
		if (fe->ops.tuner_ops.get_status) {
			if (fe->ops.i2c_gate_ctrl)
				fe->ops.i2c_gate_ctrl(fe, 1);

			fe->ops.tuner_ops.get_status(fe, &tuner_status);

			if (fe->ops.i2c_gate_ctrl)
				fe->ops.i2c_gate_ctrl(fe, 0);
		}
		if (tuner_status)
			*status |= FE_HAS_CARRIER | FE_HAS_SIGNAL;
		break;
	}
	state->fe_status = *status;

	if (*status & FE_HAS_LOCK)

		au8522_led_ctrl(state, -1);
	else

		au8522_led_ctrl(state, 0);

	dprintk("%s() status 0x%08x\n", __func__, *status);

	return 0;
}
