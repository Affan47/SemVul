dib9000_remove_slave_frontend(struct dvb_frontend *fe)
{
	struct dib9000_state *state = fe->demodulator_priv;
	u8 index_frontend = 1;

	while ((index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL))
		index_frontend++;
	if (index_frontend != 1) {
		dprintk("remove slave fe %p (index %i)", state->fe[index_frontend - 1], index_frontend - 1);
		state->fe[index_frontend] = NULL;
		return 0;
	}

	dprintk("no frontend to be removed");
	return -ENODEV;
}
