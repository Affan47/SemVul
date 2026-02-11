snd_azf3328_pcm(struct snd_azf3328 *chip)
{

	enum { AZF_PCMDEV_STD, AZF_PCMDEV_I2S_OUT, NUM_AZF_PCMDEVS };

	struct snd_pcm *pcm;
	int err;

	err = snd_pcm_new(chip->card, "AZF3328 DSP", AZF_PCMDEV_STD,
								1, 1, &pcm);
	if (err < 0)
		return err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
						&snd_azf3328_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
						&snd_azf3328_capture_ops);

	pcm->private_data = chip;
	pcm->info_flags = 0;
	strcpy(pcm->name, chip->card->shortname);

	chip->pcm[AZF_CODEC_PLAYBACK] = pcm;
	chip->pcm[AZF_CODEC_CAPTURE] = pcm;

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
						snd_dma_pci_data(chip->pci),
							64*1024, 64*1024);

	err = snd_pcm_new(chip->card, "AZF3328 I2S OUT", AZF_PCMDEV_I2S_OUT,
								1, 0, &pcm);
	if (err < 0)
		return err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
						&snd_azf3328_i2s_out_ops);

	pcm->private_data = chip;
	pcm->info_flags = 0;
	strcpy(pcm->name, chip->card->shortname);
	chip->pcm[AZF_CODEC_I2S_OUT] = pcm;

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
						snd_dma_pci_data(chip->pci),
							64*1024, 64*1024);

	return 0;
}
