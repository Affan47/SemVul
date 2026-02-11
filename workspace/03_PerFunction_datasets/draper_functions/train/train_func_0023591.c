snd_cs46xx_playback_close(struct snd_pcm_substream *substream)
{
	struct snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_cs46xx_pcm * cpcm;

	cpcm = runtime->private_data;


	if (!cpcm) return -ENXIO;

#ifdef CONFIG_SND_CS46XX_NEW_DSP
	mutex_lock(&chip->spos_mutex);
	if (cpcm->pcm_channel) {
		cs46xx_dsp_destroy_pcm_channel(chip,cpcm->pcm_channel);
		cpcm->pcm_channel = NULL;
	}
	mutex_unlock(&chip->spos_mutex);
#else
	chip->playback_pcm = NULL;
#endif

	cpcm->substream = NULL;
	snd_dma_free_pages(&cpcm->hw_buf);
	chip->active_ctrl(chip, -1);

	return 0;
}
