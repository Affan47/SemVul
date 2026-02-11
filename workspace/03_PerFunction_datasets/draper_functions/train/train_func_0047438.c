snd_hdspm_release(struct snd_pcm_substream *substream)
{
	struct hdspm *hdspm = snd_pcm_substream_chip(substream);
	bool playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);

	spin_lock_irq(&hdspm->lock);

	if (playback) {
		hdspm->playback_pid = -1;
		hdspm->playback_substream = NULL;
	} else {
		hdspm->capture_pid = -1;
		hdspm->capture_substream = NULL;
	}

	spin_unlock_irq(&hdspm->lock);

	return 0;
}
