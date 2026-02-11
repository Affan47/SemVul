snd_pcm_sw_params(snd_pcm_t *pcm, snd_pcm_sw_params_t *params)
{
	int err;

	if (CHECK_SANITY(! pcm->setup)) {
		SNDMSG("PCM not set up");
		return -EIO;
	}
	if (! params->avail_min) {
		SNDMSG("params->avail_min is 0");
		return -EINVAL;
	}
#if 0


	if (params->start_threshold <= pcm->buffer_size &&
	    params->start_threshold > (pcm->buffer_size / params->avail_min) * params->avail_min) {
		SNDMSG("params->avail_min problem for start_threshold");
		return -EINVAL;
	}
#endif
	err = pcm->ops->sw_params(pcm->op_arg, params);
	if (err < 0)
		return err;
	pcm->tstamp_mode = params->tstamp_mode;
	pcm->period_step = params->period_step;
	pcm->avail_min = params->avail_min;
	pcm->period_event = params->period_event;
	pcm->start_threshold = params->start_threshold;
	pcm->stop_threshold = params->stop_threshold;
	pcm->silence_threshold = params->silence_threshold;
	pcm->silence_size = params->silence_size;
	pcm->boundary = params->boundary;
	return 0;
}
