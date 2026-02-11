stv0900_read_signal_strength(struct dvb_frontend *fe, u16 *strength)
{
	struct stv0900_state *state = fe->demodulator_priv;
	struct stv0900_internal *internal = state->internal;
	s32 rflevel = stv0900_get_rf_level(internal, &stv0900_rf,
								state->demod);

	rflevel = (rflevel + 100) * (65535 / 70);
	if (rflevel < 0)
		rflevel = 0;

	if (rflevel > 65535)
		rflevel = 65535;

	*strength = rflevel;

	return 0;
}
