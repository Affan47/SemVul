capture_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct ua101 *ua = substream->private_data;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		if (!test_bit(USB_CAPTURE_RUNNING, &ua->states))
			return -EIO;
		set_bit(ALSA_CAPTURE_RUNNING, &ua->states);
		return 0;
	case SNDRV_PCM_TRIGGER_STOP:
		clear_bit(ALSA_CAPTURE_RUNNING, &ua->states);
		return 0;
	default:
		return -EINVAL;
	}
}
