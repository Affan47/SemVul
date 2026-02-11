mxl5007t_attach(struct dvb_frontend *fe,
				     struct i2c_adapter *i2c, u8 addr,
				     struct mxl5007t_config *cfg)
{
	struct mxl5007t_state *state = NULL;
	int instance, ret;

	mutex_lock(&mxl5007t_list_mutex);
	instance = hybrid_tuner_request_state(struct mxl5007t_state, state,
					      hybrid_tuner_instance_list,
					      i2c, addr, "mxl5007t");
	switch (instance) {
	case 0:
		goto fail;
	case 1:

		state->config = cfg;

		mutex_init(&state->lock);

		if (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		ret = mxl5007t_get_chip_id(state);

		if (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);


		if (mxl_fail(ret))
			goto fail;
		break;
	default:

		break;
	}

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	ret = mxl5007t_soft_reset(state);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	if (mxl_fail(ret))
		goto fail;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	ret = mxl5007t_write_reg(state, 0x04,
		state->config->loop_thru_enable);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	if (mxl_fail(ret))
		goto fail;

	fe->tuner_priv = state;

	mutex_unlock(&mxl5007t_list_mutex);

	memcpy(&fe->ops.tuner_ops, &mxl5007t_tuner_ops,
	       sizeof(struct dvb_tuner_ops));

	return fe;
fail:
	mutex_unlock(&mxl5007t_list_mutex);

	mxl5007t_release(fe);
	return NULL;
}
