snd_es1968_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct es1968 *chip = snd_pcm_substream_chip(substream);
	struct esschan *es = substream->runtime->private_data;

	spin_lock(&chip->substream_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		if (es->running)
			break;
		snd_es1968_bob_inc(chip, es->bob_freq);
		es->count = 0;
		es->hwptr = 0;
		snd_es1968_pcm_start(chip, es);
		es->running = 1;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		if (! es->running)
			break;
		snd_es1968_pcm_stop(chip, es);
		es->running = 0;
		snd_es1968_bob_dec(chip);
		break;
	}
	spin_unlock(&chip->substream_lock);
	return 0;
}
