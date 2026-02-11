fdtv_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct firedtv *fdtv = fe->sec_priv;
	struct firedtv_tuner_status stat;

	if (avc_tuner_status(fdtv, &stat))
		return -EINVAL;


	*snr = stat.carrier_noise_ratio * 257;
	return 0;
}
