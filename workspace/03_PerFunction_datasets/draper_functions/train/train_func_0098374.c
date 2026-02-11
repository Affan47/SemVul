snd_atiixp_pcm_hw_params(struct snd_pcm_substream *substream,
				   struct snd_pcm_hw_params *hw_params)
{
	struct atiixp_modem *chip = snd_pcm_substream_chip(substream);
	struct atiixp_dma *dma = substream->runtime->private_data;
	int err;
	int i;

	err = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params));
	if (err < 0)
		return err;
	dma->buf_addr = substream->runtime->dma_addr;
	dma->buf_bytes = params_buffer_bytes(hw_params);

	err = atiixp_build_dma_packets(chip, dma, substream,
				       params_periods(hw_params),
				       params_period_bytes(hw_params));
	if (err < 0)
		return err;


	for (i = 0; i < NUM_ATI_CODECS; i++) {
		if (! chip->ac97[i])
			continue;
		snd_ac97_write(chip->ac97[i], AC97_LINE1_RATE, params_rate(hw_params));
		snd_ac97_write(chip->ac97[i], AC97_LINE1_LEVEL, 0);
	}

	return err;
}
