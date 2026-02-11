dsp_buffer_free(struct snd_pcm_substream *substream)
{
	struct snd_tm6000_card *chip = snd_pcm_substream_chip(substream);

	dprintk(2, "Freeing buffer\n");

	vfree(substream->runtime->dma_area);
	substream->runtime->dma_area = NULL;
	substream->runtime->dma_bytes = 0;
}
