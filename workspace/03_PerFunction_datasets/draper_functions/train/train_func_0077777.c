drxd_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct drxd_state *state = fe->demodulator_priv;
	u32 lock;

	DRXD_status(state, &lock);
	*status = 0;

#if 1
	if (lock & DRX_LOCK_MPEG)
		*status |= FE_HAS_LOCK;
#else
	if (lock & DRX_LOCK_FEC)
		*status |= FE_HAS_LOCK;
#endif
	if (lock & DRX_LOCK_FEC)
		*status |= FE_HAS_VITERBI | FE_HAS_SYNC;
	if (lock & DRX_LOCK_DEMOD)
		*status |= FE_HAS_CARRIER | FE_HAS_SIGNAL;

	return 0;
}
