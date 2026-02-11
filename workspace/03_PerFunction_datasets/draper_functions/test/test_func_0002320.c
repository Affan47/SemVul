snd_intel8x0m_pcm1(struct intel8x0m *chip, int device,
			      struct ich_pcm_table *rec)
{
	struct snd_pcm *pcm;
	int err;
	char name[32];

	if (rec->suffix)
		sprintf(name, "Intel ICH - %s", rec->suffix);
	else
		strcpy(name, "Intel ICH");
	err = snd_pcm_new(chip->card, name, device,
			  rec->playback_ops ? 1 : 0,
			  rec->capture_ops ? 1 : 0, &pcm);
	if (err < 0)
		return err;

	if (rec->playback_ops)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, rec->playback_ops);
	if (rec->capture_ops)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, rec->capture_ops);

	pcm->private_data = chip;
	pcm->info_flags = 0;
	pcm->dev_class = SNDRV_PCM_CLASS_MODEM;
	if (rec->suffix)
		sprintf(pcm->name, "%s - %s", chip->card->shortname, rec->suffix);
	else
		strcpy(pcm->name, chip->card->shortname);
	chip->pcm[device] = pcm;

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(chip->pci),
					      rec->prealloc_size,
					      rec->prealloc_max_size);

	return 0;
}
