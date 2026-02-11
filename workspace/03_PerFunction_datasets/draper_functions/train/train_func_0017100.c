snd_pcm_pre_prepare(struct snd_pcm_substream *substream,
			       int f_flags)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	if (runtime->status->state == SNDRV_PCM_STATE_OPEN ||
	    runtime->status->state == SNDRV_PCM_STATE_DISCONNECTED)
		return -EBADFD;
	if (snd_pcm_running(substream))
		return -EBUSY;
	substream->f_flags = f_flags;
	return 0;
}
