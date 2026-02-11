snd_pcm_lib_preallocate_pages1(struct snd_pcm_substream *substream,
					  size_t size, size_t max)
{

	if (size > 0 && preallocate_dma && substream->number < maximum_substreams)
		preallocate_pcm_pages(substream, size);

	if (substream->dma_buffer.bytes > 0)
		substream->buffer_bytes_max = substream->dma_buffer.bytes;
	substream->dma_max = max;
	preallocate_info_init(substream);
	return 0;
}
