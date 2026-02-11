snd_dmaengine_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct dmaengine_pcm_runtime_data *prtd = substream_to_prtd(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int ret;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		ret = dmaengine_pcm_prepare_and_submit(substream);
		if (ret)
			return ret;
		dma_async_issue_pending(prtd->dma_chan);
		break;
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		dmaengine_resume(prtd->dma_chan);
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
		if (runtime->info & SNDRV_PCM_INFO_PAUSE)
			dmaengine_pause(prtd->dma_chan);
		else
			dmaengine_terminate_all(prtd->dma_chan);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		dmaengine_pause(prtd->dma_chan);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		dmaengine_terminate_all(prtd->dma_chan);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
