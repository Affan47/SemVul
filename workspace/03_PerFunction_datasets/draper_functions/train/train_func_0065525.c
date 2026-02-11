stb0899_sleep(struct dvb_frontend *fe)
{
	struct stb0899_state *state = fe->demodulator_priv;


	dprintk(state->verbose, FE_DEBUG, 1, "Going to Sleep .. (Really tired .. :-))");

	stb0899_postproc(state, STB0899_POSTPROC_GPIO_POWER, 0);

	return 0;
}
