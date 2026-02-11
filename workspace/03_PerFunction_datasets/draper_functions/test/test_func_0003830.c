ltc_encoder_reinit(LTCEncoder *e, double sample_rate, double fps, enum LTC_TV_STANDARD standard, int flags) {
	if (sample_rate < 1)
		return -1;

	size_t bufsize = 1 + ceil(sample_rate / fps);
	if (bufsize > e->bufsize) {
		return -1;
	}

	e->state = 0;
	e->offset = 0;
	e->sample_rate = sample_rate;
	ltc_encoder_set_filter(e, 40.0);
	e->fps = fps;
	e->flags = flags;
	e->standard = standard;
	e->samples_per_clock = sample_rate / (fps * 80.0);
	e->samples_per_clock_2 = e->samples_per_clock / 2.0;
	e->sample_remainder = 0.5;

	if (flags & LTC_BGF_DONT_TOUCH) {
		e->f.col_frame = 0;
		if (flags&LTC_TC_CLOCK) {
			e->f.binary_group_flag_bit1 = 1;
		} else {
			e->f.binary_group_flag_bit1 = 0;
		}
		switch (standard) {
			case LTC_TV_625_50:
				e->f.biphase_mark_phase_correction = 0;
				e->f.binary_group_flag_bit0 = (flags&LTC_USE_DATE)?1:0;
				break;
			default:
				e->f.binary_group_flag_bit0 = 0;
				e->f.binary_group_flag_bit2 = (flags&LTC_USE_DATE)?1:0;
				break;
		}
	}
	if ((flags&LTC_NO_PARITY) == 0) {
		ltc_frame_set_parity(&e->f, standard);
	}

	if (rint(fps*100) == 2997)
		e->f.dfbit = 1;
	else
		e->f.dfbit = 0;
	return 0;
}
