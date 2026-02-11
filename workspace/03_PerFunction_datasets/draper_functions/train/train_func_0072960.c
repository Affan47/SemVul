xrun()
{
	snd_pcm_status_t *status;

	if(s_pcm_status_malloc(&status) < 0) {
		return 0;
	}

	if(s_pcm_status(alsa_handler, status) < 0) {
		s_pcm_status_free(status);
		return 0;
	}

	if(s_pcm_status_get_state(status) == SND_PCM_STATE_XRUN) {
		struct timeval now, diff, tstamp;
		gettimeofday(&now, 0);
		s_pcm_status_get_trigger_tstamp(status, &tstamp);
		timersub(&now, &tstamp, &diff);
	}

	s_pcm_status_free(status);

	if(s_pcm_prepare(alsa_handler) < 0) {
		return 0;
	}

	return 1;
}
