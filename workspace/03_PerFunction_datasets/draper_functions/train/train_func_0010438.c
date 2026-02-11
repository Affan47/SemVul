snd_nm256_playback_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct nm256 *chip = snd_pcm_substream_chip(substream);
	struct nm256_stream *s = substream->runtime->private_data;
	int err = 0;

	if (snd_BUG_ON(!s))
		return -ENXIO;

	spin_lock(&chip->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_RESUME:
		s->suspended = 0;

	case SNDRV_PCM_TRIGGER_START:
		if (! s->running) {
			snd_nm256_playback_start(chip, s, substream);
			s->running = 1;
		}
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
		s->suspended = 1;

	case SNDRV_PCM_TRIGGER_STOP:
		if (s->running) {
			snd_nm256_playback_stop(chip);
			s->running = 0;
		}
		break;
	default:
		err = -EINVAL;
		break;
	}
	spin_unlock(&chip->reg_lock);
	return err;
}
