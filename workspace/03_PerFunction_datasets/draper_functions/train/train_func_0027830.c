snd_pcm_do_pause(struct snd_pcm_substream *substream, int push)
{
	if (substream->runtime->trigger_master != substream)
		return 0;


	if (push)
		snd_pcm_update_hw_ptr(substream);


	substream->runtime->hw_ptr_jiffies = jiffies - HZ * 1000;
	return substream->ops->trigger(substream,
				       push ? SNDRV_PCM_TRIGGER_PAUSE_PUSH :
					      SNDRV_PCM_TRIGGER_PAUSE_RELEASE);
}
