drxk_sleep(struct dvb_frontend *fe)
{
	struct drxk_state *state = fe->demodulator_priv;

	dprintk(1, "\n");

	if (state->m_drxk_state == DRXK_NO_DEV)
		return -ENODEV;
	if (state->m_drxk_state == DRXK_UNINITIALIZED)
		return 0;

	shut_down(state);
	return 0;
}
