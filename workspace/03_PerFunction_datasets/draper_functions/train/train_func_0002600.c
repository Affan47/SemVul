stv0900_get_standard(struct dvb_frontend *fe,
						enum fe_stv0900_demod_num demod)
{
	struct stv0900_state *state = fe->demodulator_priv;
	struct stv0900_internal *intp = state->internal;
	enum fe_stv0900_tracking_standard fnd_standard;

	int hdr_mode = stv0900_get_bits(intp, HEADER_MODE);

	switch (hdr_mode) {
	case 2:
		fnd_standard = STV0900_DVBS2_STANDARD;
		break;
	case 3:
		if (stv0900_get_bits(intp, DSS_DVB) == 1)
			fnd_standard = STV0900_DSS_STANDARD;
		else
			fnd_standard = STV0900_DVBS1_STANDARD;

		break;
	default:
		fnd_standard = STV0900_UNKNOWN_STANDARD;
	}

	dprintk("%s: standard %d\n", __func__, fnd_standard);

	return fnd_standard;
}
