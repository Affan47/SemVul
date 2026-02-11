snd_es1938_playback2_pointer(struct snd_pcm_substream *substream)
{
	struct es1938 *chip = snd_pcm_substream_chip(substream);
	size_t ptr;
	size_t old, new;
#if 1

	old = inw(SLDM_REG(chip, DMACOUNT));
	while ((new = inw(SLDM_REG(chip, DMACOUNT))) != old)
		old = new;
	ptr = chip->dma1_size - 1 - new;
#else
	ptr = inl(SLDM_REG(chip, DMAADDR)) - chip->dma1_start;
#endif
	return ptr >> chip->dma1_shift;
}
