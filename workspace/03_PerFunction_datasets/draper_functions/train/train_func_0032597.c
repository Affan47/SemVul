snd_ymfpci_pcm(struct snd_ymfpci *chip, int device)
{
	struct snd_pcm *pcm;
	int err;

	if ((err = snd_pcm_new(chip->card, "YMFPCI", device, 32, 1, &pcm)) < 0)
		return err;
	pcm->private_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ymfpci_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_ymfpci_capture_rec_ops);


	pcm->info_flags = 0;
	strcpy(pcm->name, "YMFPCI");
	chip->pcm = pcm;

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(chip->pci), 64*1024, 256*1024);

	return snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     snd_pcm_std_chmaps, 2, 0, NULL);
}
