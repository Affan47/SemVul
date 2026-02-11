stv0900_stop_ts(struct dvb_frontend *fe, int stop_ts)
{

	struct stv0900_state *state = fe->demodulator_priv;
	struct stv0900_internal *intp = state->internal;
	enum fe_stv0900_demod_num demod = state->demod;

	if (stop_ts == TRUE)
		stv0900_write_bits(intp, RST_HWARE, 1);
	else
		stv0900_write_bits(intp, RST_HWARE, 0);

	return 0;
}
