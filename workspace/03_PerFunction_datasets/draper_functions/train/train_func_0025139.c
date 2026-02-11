si2165_sleep(struct dvb_frontend *fe)
{
	int ret;
	struct si2165_state *state = fe->demodulator_priv;


	ret = si2165_writereg8(state, 0x0104, 0x00);
	if (ret < 0)
		return ret;

	ret = si2165_writereg8(state, 0x0000, SI2165_MODE_OFF);
	if (ret < 0)
		return ret;
	return 0;
}
