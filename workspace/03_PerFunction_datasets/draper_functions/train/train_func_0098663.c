_scale_tail_taps(struct audio_plugin_t *p)
{
	delay_t *d = (delay_t *)p->user;
	unsigned i, t, scale;

	float s_ms = (float)p->ctl[FXC_SAMPLERATE] * 0.001;
	s_ms *= (float)p->ctl[DC_TAIL_TIME];
	s_ms *= 1.0/1024.0;
	scale = (unsigned)s_ms;
	for(t = 0, i = 0; i < DELAY_MAX_TAIL_TAPS; ++i)
	{
		unsigned delay;
		int shift;
		if(!p->ctl[DC_TAIL_TAP_1_LEVEL + i*2])
			continue;

		shift = fixp2shift(p->ctl[DC_TAIL_TAP_1_LEVEL + i*2]);
		delay = (unsigned)p->ctl[DC_TAIL_TAP_1_TIME + i*2] >> 8;
		delay *= scale;
		delay >>= 14;
		if(delay > DELAY_BUFSIZE-2)
			delay = DELAY_BUFSIZE-2;
		delay &= (DELAY_MASK-1);
		delay |= (t>>1) & 1;
		d->tailtap[t].delay = delay;
		d->tailtap[t].shift = shift;
		++t;
	}
	d->tailtaps = t;
}
