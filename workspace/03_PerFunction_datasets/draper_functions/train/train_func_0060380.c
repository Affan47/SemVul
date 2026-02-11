eat_words(const uint32_t **buf, const uint32_t *buf_end, unsigned num_words)
{
	if ((buf_end - *buf) >= num_words) {
		*buf += num_words;
		return 0;
	}
	DRM_ERROR("Illegal termination of DMA command buffer\n");
	return 1;
}
