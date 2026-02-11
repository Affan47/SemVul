snd_es1938_new_pcm(struct es1938 *chip, int device)
{
	struct snd_pcm *pcm;
	int err;

	if ((err = snd_pcm_new(chip->card, "es-1938-1946", device, 2, 1, &pcm)) < 0)
		return err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_es1938_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_es1938_capture_ops);

	pcm->private_data = chip;
	pcm->info_flags = 0;
	strcpy(pcm->name, "ESS Solo-1");

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(chip->pci), 64*1024, 64*1024);

	chip->pcm = pcm;
	return 0;
}
