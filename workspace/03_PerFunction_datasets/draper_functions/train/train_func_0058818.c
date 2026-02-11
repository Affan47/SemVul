dib9000_read_snr(struct dvb_frontend *fe, u16 * snr)
{
	struct dib9000_state *state = fe->demodulator_priv;
	u8 index_frontend;
	u32 snr_master;

	if (mutex_lock_interruptible(&state->demod_lock) < 0) {
		dprintk("could not get the lock");
		return -EINTR;
	}
	snr_master = dib9000_get_snr(fe);
	for (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL); index_frontend++)
		snr_master += dib9000_get_snr(state->fe[index_frontend]);

	if ((snr_master >> 16) != 0) {
		snr_master = 10 * intlog10(snr_master >> 16);
		*snr = snr_master / ((1 << 24) / 10);
	} else
		*snr = 0;

	mutex_unlock(&state->demod_lock);

	return 0;
}
