usb6fire_pcm_pointer(
		struct snd_pcm_substream *alsa_sub)
{
	struct pcm_substream *sub = usb6fire_pcm_get_substream(alsa_sub);
	struct pcm_runtime *rt = snd_pcm_substream_chip(alsa_sub);
	unsigned long flags;
	snd_pcm_uframes_t ret;

	if (rt->panic || !sub)
		return SNDRV_PCM_POS_XRUN;

	spin_lock_irqsave(&sub->lock, flags);
	ret = sub->dma_off;
	spin_unlock_irqrestore(&sub->lock, flags);
	return ret;
}
