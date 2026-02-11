qm1d1c0042_sleep(struct dvb_frontend *fe)
{
	struct qm1d1c0042_state *state;
	int ret;

	state = fe->tuner_priv;
	state->regs[0x01] &= (~(1 << 3)) & 0xff;
	state->regs[0x01] |= 1 << 0;
	state->regs[0x05] |= 1 << 3;
	ret = reg_write(state, 0x05, state->regs[0x05]);
	if (ret == 0)
		ret = reg_write(state, 0x01, state->regs[0x01]);
	if (ret < 0)
		dev_warn(&state->i2c->dev, "(%s) failed. [adap%d-fe%d]\n",
			__func__, fe->dvb->num, fe->id);
	return ret;
}
