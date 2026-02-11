biphase_decode2(LTCDecoder *d, int offset, ltc_off_t pos) {

	d->biphase_tics[d->biphase_tic] = d->snd_to_biphase_period;
	d->biphase_tic = (d->biphase_tic + 1) % LTC_FRAME_BIT_COUNT;
	if (d->snd_to_biphase_cnt <= 2 * d->snd_to_biphase_period) {
		pos -= (d->snd_to_biphase_period - d->snd_to_biphase_cnt);
	}

	if (d->snd_to_biphase_state == d->biphase_prev) {
		d->biphase_state = 1;
		parse_ltc(d, 0, offset, pos);
	} else {
		d->biphase_state = 1 - d->biphase_state;
		if (d->biphase_state == 1) {
			parse_ltc(d, 1, offset, pos);
		}
	}
	d->biphase_prev = d->snd_to_biphase_state;
}
