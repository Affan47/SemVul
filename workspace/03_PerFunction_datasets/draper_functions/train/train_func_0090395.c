snd_cs46xx_playback_direct_pointer(struct snd_pcm_substream *substream)
{
	struct snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	size_t ptr;
	struct snd_cs46xx_pcm *cpcm = substream->runtime->private_data;

	if (snd_BUG_ON(!cpcm->pcm_channel))
		return -ENXIO;

#ifdef CONFIG_SND_CS46XX_NEW_DSP
	ptr = snd_cs46xx_peek(chip, (cpcm->pcm_channel->pcm_reader_scb->address + 2) << 2);
#else
	ptr = snd_cs46xx_peek(chip, BA1_PBA);
#endif
	ptr -= cpcm->hw_buf.addr;
	return ptr >> cpcm->shift;
}
