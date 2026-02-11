dsp_tone(struct dsp *dsp, int tone)
{
	struct pattern *pat;
	int i;
	struct dsp_tone *tonet = &dsp->tone;

	tonet->software = 0;
	tonet->hardware = 0;


	if (!tone) {
		if (dsp->features.hfc_loops && timer_pending(&tonet->tl))
			del_timer(&tonet->tl);
		if (dsp->features.hfc_loops)
			dsp_tone_hw_message(dsp, NULL, 0);
		tonet->tone = 0;
		return 0;
	}

	pat = NULL;
	i = 0;
	while (pattern[i].tone) {
		if (pattern[i].tone == tone) {
			pat = &pattern[i];
			break;
		}
		i++;
	}
	if (!pat) {
		printk(KERN_WARNING "dsp: given tone 0x%x is invalid\n", tone);
		return -EINVAL;
	}
	if (dsp_debug & DEBUG_DSP_TONE)
		printk(KERN_DEBUG "%s: now starting tone %d (index=%d)\n",
		       __func__, tone, 0);
	tonet->tone = tone;
	tonet->pattern = pat;
	tonet->index = 0;
	tonet->count = 0;

	if (dsp->features.hfc_loops) {
		tonet->hardware = 1;

		dsp_tone_hw_message(dsp, pat->data[0], *(pat->siz[0]));

		if (timer_pending(&tonet->tl))
			del_timer(&tonet->tl);
		init_timer(&tonet->tl);
		tonet->tl.expires = jiffies + (pat->seq[0] * HZ) / 8000;
		add_timer(&tonet->tl);
	} else {
		tonet->software = 1;
	}

	return 0;
}
