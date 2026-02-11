ltc_encoder_set_volume(LTCEncoder *e, double dBFS) {
	if (dBFS > 0)
		return -1;
	double pp = rint(127.0 * pow(10, dBFS/20.0));
	if (pp < 1 || pp > 127)
		return -1;
	ltcsnd_sample_t diff = ((ltcsnd_sample_t) pp)&0x7f;
	e->enc_lo = SAMPLE_CENTER - diff;
	e->enc_hi = SAMPLE_CENTER + diff;
	return 0;
}
