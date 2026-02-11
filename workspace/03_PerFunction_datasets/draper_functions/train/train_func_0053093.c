m88rs2000_init(struct dvb_frontend *fe)
{
	struct m88rs2000_state *state = fe->demodulator_priv;
	int ret;

	deb_info("m88rs2000: init chip\n");

	if (state->config->inittab)
		ret = m88rs2000_tab_set(state,
				(struct inittab *)state->config->inittab);
	else
		ret = m88rs2000_tab_set(state, m88rs2000_setup);

	return ret;
}
