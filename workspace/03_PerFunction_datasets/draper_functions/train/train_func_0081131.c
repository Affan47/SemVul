snd_pcm_rate_status(snd_pcm_t *pcm, snd_pcm_status_t * status)
{
	snd_pcm_rate_t *rate = pcm->private_data;
	snd_pcm_sframes_t err;
	snd_atomic_read_t ratom;
	snd_atomic_read_init(&ratom, &rate->watom);
 _again:
	snd_atomic_read_begin(&ratom);
	err = snd_pcm_status(rate->gen.slave, status);
	if (err < 0) {
		snd_atomic_read_ok(&ratom);
		return err;
	}
	if (pcm->stream == SND_PCM_STREAM_PLAYBACK) {
		if (rate->start_pending)
			status->state = SND_PCM_STATE_RUNNING;
		status->trigger_tstamp = rate->trigger_tstamp;
	}
	snd_pcm_rate_sync_hwptr(pcm);
	status->appl_ptr = *pcm->appl.ptr;
	status->hw_ptr = *pcm->hw.ptr;
	if (pcm->stream == SND_PCM_STREAM_PLAYBACK) {
		status->delay = snd_pcm_mmap_playback_hw_avail(pcm);
		status->avail = snd_pcm_mmap_playback_avail(pcm);
		status->avail_max = rate->ops.input_frames(rate->obj, status->avail_max);
	} else {
		status->delay = snd_pcm_mmap_capture_hw_avail(pcm);
		status->avail = snd_pcm_mmap_capture_avail(pcm);
		status->avail_max = rate->ops.output_frames(rate->obj, status->avail_max);
	}
	if (!snd_atomic_read_ok(&ratom)) {
		snd_atomic_read_wait(&ratom);
		goto _again;
	}
	return 0;
}
