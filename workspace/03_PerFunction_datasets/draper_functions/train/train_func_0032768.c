fsl_asrc_dma_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct fsl_asrc_pair *pair = runtime->private_data;
	int ret;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = fsl_asrc_dma_prepare_and_submit(substream);
		if (ret)
			return ret;
		dma_async_issue_pending(pair->dma_chan[IN]);
		dma_async_issue_pending(pair->dma_chan[OUT]);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		dmaengine_terminate_all(pair->dma_chan[OUT]);
		dmaengine_terminate_all(pair->dma_chan[IN]);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
