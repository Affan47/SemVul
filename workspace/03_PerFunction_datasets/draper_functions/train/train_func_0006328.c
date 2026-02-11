snd_pcm_do_start(struct snd_pcm_substream *substream, int state)
{
	if (substream->runtime->trigger_master != substream)
		return 0;
	return substream->ops->trigger(substream, SNDRV_PCM_TRIGGER_START);
}
