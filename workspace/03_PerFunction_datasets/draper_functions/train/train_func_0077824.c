snd_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime;
	int result = 0;

	if (PCM_RUNTIME_CHECK(substream))
		return -ENXIO;
	runtime = substream->runtime;
	snd_pcm_stream_lock_irq(substream);
	switch (runtime->status->state) {
	case SNDRV_PCM_STATE_SETUP:
	case SNDRV_PCM_STATE_PREPARED:
		break;
	default:
		snd_pcm_stream_unlock_irq(substream);
		return -EBADFD;
	}
	snd_pcm_stream_unlock_irq(substream);
	if (atomic_read(&substream->mmap_count))
		return -EBADFD;
	if (substream->ops->hw_free)
		result = substream->ops->hw_free(substream);
	snd_pcm_set_state(substream, SNDRV_PCM_STATE_OPEN);
	pm_qos_remove_request(&substream->latency_pm_qos_req);
	return result;
}
