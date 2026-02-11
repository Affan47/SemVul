snd_hdspm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct hdspm *hdspm = snd_pcm_substream_chip(substream);
	struct snd_pcm_substream *other;
	int running;

	spin_lock(&hdspm->lock);
	running = hdspm->running;
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		running |= 1 << substream->stream;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		running &= ~(1 << substream->stream);
		break;
	default:
		snd_BUG();
		spin_unlock(&hdspm->lock);
		return -EINVAL;
	}
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		other = hdspm->capture_substream;
	else
		other = hdspm->playback_substream;

	if (other) {
		struct snd_pcm_substream *s;
		snd_pcm_group_for_each_entry(s, substream) {
			if (s == other) {
				snd_pcm_trigger_done(s, substream);
				if (cmd == SNDRV_PCM_TRIGGER_START)
					running |= 1 << s->stream;
				else
					running &= ~(1 << s->stream);
				goto _ok;
			}
		}
		if (cmd == SNDRV_PCM_TRIGGER_START) {
			if (!(running & (1 << SNDRV_PCM_STREAM_PLAYBACK))
					&& substream->stream ==
					SNDRV_PCM_STREAM_CAPTURE)
				hdspm_silence_playback(hdspm);
		} else {
			if (running &&
				substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
				hdspm_silence_playback(hdspm);
		}
	} else {
		if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			hdspm_silence_playback(hdspm);
	}
_ok:
	snd_pcm_trigger_done(substream, substream);
	if (!hdspm->running && running)
		hdspm_start_audio(hdspm);
	else if (hdspm->running && !running)
		hdspm_stop_audio(hdspm);
	hdspm->running = running;
	spin_unlock(&hdspm->lock);

	return 0;
}
