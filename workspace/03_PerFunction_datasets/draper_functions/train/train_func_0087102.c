snd_via686_pcm_new(struct via82xx *chip)
{
	struct snd_pcm *pcm;
	int err;

	chip->playback_devno = 0;
	chip->capture_devno = 1;
	chip->num_devs = 2;
	chip->intr_mask = 0x77;

	err = snd_pcm_new(chip->card, chip->card->shortname, 0, 1, 1, &pcm);
	if (err < 0)
		return err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_via686_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_via686_capture_ops);
	pcm->private_data = chip;
	strcpy(pcm->name, chip->card->shortname);
	chip->pcms[0] = pcm;
	init_viadev(chip, 0, VIA_REG_PLAYBACK_STATUS, 0, 0);
	init_viadev(chip, 1, VIA_REG_CAPTURE_STATUS, 0, 1);

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
					      snd_dma_pci_data(chip->pci),
					      64*1024, VIA_MAX_BUFSIZE);
	return 0;
}
