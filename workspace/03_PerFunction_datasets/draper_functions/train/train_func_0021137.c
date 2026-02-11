snd_dmaengine_pcm_register(struct device *dev,
	const struct snd_dmaengine_pcm_config *config, unsigned int flags)
{
	struct dmaengine_pcm *pcm;
	int ret;

	pcm = kzalloc(sizeof(*pcm), GFP_KERNEL);
	if (!pcm)
		return -ENOMEM;

	pcm->config = config;
	pcm->flags = flags;

	ret = dmaengine_pcm_request_chan_of(pcm, dev, config);
	if (ret)
		goto err_free_dma;

	ret = snd_soc_add_platform(dev, &pcm->platform,
		&dmaengine_pcm_platform);
	if (ret)
		goto err_free_dma;

	return 0;

err_free_dma:
	dmaengine_pcm_release_chan(pcm);
	kfree(pcm);
	return ret;
}
