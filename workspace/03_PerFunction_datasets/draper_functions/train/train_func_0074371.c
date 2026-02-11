dvbsky_usb_read_status(struct dvb_frontend *fe,
				  enum fe_status *status)
{
	struct dvb_usb_device *d = fe_to_d(fe);
	struct dvbsky_state *state = d_to_priv(d);
	int ret;

	ret = state->fe_read_status(fe, status);


	if ((*status & FE_HAS_LOCK) && (!state->last_lock))
		dvbsky_stream_ctrl(d, 1);

	state->last_lock = (*status & FE_HAS_LOCK) ? 1 : 0;
	return ret;
}
