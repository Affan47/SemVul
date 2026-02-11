s5h1409_attach(const struct s5h1409_config *config,
				    struct i2c_adapter *i2c)
{
	struct s5h1409_state *state = NULL;
	u16 reg;


	state = kzalloc(sizeof(struct s5h1409_state), GFP_KERNEL);
	if (state == NULL)
		goto error;


	state->config = config;
	state->i2c = i2c;
	state->current_modulation = 0;
	state->if_freq = S5H1409_VSB_IF_FREQ;


	reg = s5h1409_readreg(state, 0x04);
	if ((reg != 0x0066) && (reg != 0x007f))
		goto error;


	memcpy(&state->frontend.ops, &s5h1409_ops,
	       sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	if (s5h1409_init(&state->frontend) != 0) {
		printk(KERN_ERR "%s: Failed to initialize correctly\n",
			__func__);
		goto error;
	}


	s5h1409_i2c_gate_ctrl(&state->frontend, 1);

	return &state->frontend;

error:
	kfree(state);
	return NULL;
}
