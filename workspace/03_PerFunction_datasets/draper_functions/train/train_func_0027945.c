s921_attach(const struct s921_config *config,
				    struct i2c_adapter *i2c)
{

	struct s921_state *state =
		kzalloc(sizeof(struct s921_state), GFP_KERNEL);

	dprintk("\n");
	if (!state) {
		rc("Unable to kzalloc\n");
		return NULL;
	}


	state->config = config;
	state->i2c = i2c;


	memcpy(&state->frontend.ops, &s921_ops,
		sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	return &state->frontend;
}
