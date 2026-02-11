nxt200x_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct nxt200x_state* state = fe->demodulator_priv;
	u8 lock;
	nxt200x_readbytes(state, 0x31, &lock, 1);

	*status = 0;
	if (lock & 0x20) {
		*status |= FE_HAS_SIGNAL;
		*status |= FE_HAS_CARRIER;
		*status |= FE_HAS_VITERBI;
		*status |= FE_HAS_SYNC;
		*status |= FE_HAS_LOCK;
	}
	return 0;
}
