vp702x_fe_read_status(struct dvb_frontend *fe,
				 enum fe_status *status)
{
	struct vp702x_fe_state *st = fe->demodulator_priv;
	vp702x_fe_refresh_state(st);
	deb_fe("%s\n",__func__);

	if (st->lock == 0)
		*status = FE_HAS_LOCK | FE_HAS_SYNC | FE_HAS_VITERBI | FE_HAS_SIGNAL | FE_HAS_CARRIER;
	else
		*status = 0;

	if (*status & FE_HAS_LOCK)
		st->status_check_interval = 1000;
	else
		st->status_check_interval = 250;
	return 0;
}
