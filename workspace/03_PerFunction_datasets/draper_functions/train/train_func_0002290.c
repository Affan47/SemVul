isight_samples(struct isight *isight,
			   const __be16 *samples, unsigned int count)
{
	struct snd_pcm_runtime *runtime;
	unsigned int count1;

	if (!ACCESS_ONCE(isight->pcm_running))
		return;

	runtime = isight->pcm->runtime;
	if (isight->buffer_pointer + count <= runtime->buffer_size) {
		memcpy(runtime->dma_area + isight->buffer_pointer * 4,
		       samples, count * 4);
	} else {
		count1 = runtime->buffer_size - isight->buffer_pointer;
		memcpy(runtime->dma_area + isight->buffer_pointer * 4,
		       samples, count1 * 4);
		samples += count1 * 2;
		memcpy(runtime->dma_area, samples, (count - count1) * 4);
	}

	isight_update_pointers(isight, count);
}
