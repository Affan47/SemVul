tda8261_attach(struct dvb_frontend *fe,
				    const struct tda8261_config *config,
				    struct i2c_adapter *i2c)
{
	struct tda8261_state *state = NULL;

	if ((state = kzalloc(sizeof (struct tda8261_state), GFP_KERNEL)) == NULL)
		goto exit;

	state->config		= config;
	state->i2c		= i2c;
	state->fe		= fe;
	fe->tuner_priv		= state;
	fe->ops.tuner_ops	= tda8261_ops;

	fe->ops.tuner_ops.info.frequency_step = div_tab[config->step_size];


	pr_info("%s: Attaching TDA8261 8PSK/QPSK tuner\n", __func__);

	return fe;

exit:
	kfree(state);
	return NULL;
}
