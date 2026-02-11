snd_ca0106_probe(struct pci_dev *pci,
					const struct pci_device_id *pci_id)
{
	static int dev;
	struct snd_card *card;
	struct snd_ca0106 *chip;
	int i, err;

	if (dev >= SNDRV_CARDS)
		return -ENODEV;
	if (!enable[dev]) {
		dev++;
		return -ENOENT;
	}

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	if (err < 0)
		return err;

	err = snd_ca0106_create(dev, card, pci, &chip);
	if (err < 0)
		goto error;
	card->private_data = chip;

	for (i = 0; i < 4; i++) {
		err = snd_ca0106_pcm(chip, i);
		if (err < 0)
			goto error;
	}

	if (chip->details->ac97 == 1) {

		err = snd_ca0106_ac97(chip);
		if (err < 0)
			goto error;
	}
	err = snd_ca0106_mixer(chip);
	if (err < 0)
		goto error;

	dev_dbg(card->dev, "probe for MIDI channel A ...");
	err = snd_ca0106_midi(chip, CA0106_MIDI_CHAN_A);
	if (err < 0)
		goto error;
	dev_dbg(card->dev, " done.\n");

#ifdef CONFIG_SND_PROC_FS
	snd_ca0106_proc_init(chip);
#endif

	err = snd_card_register(card);
	if (err < 0)
		goto error;

	pci_set_drvdata(pci, card);
	dev++;
	return 0;

 error:
	snd_card_free(card);
	return err;
}
