snd_via82xx_create(struct snd_card *card,
			      struct pci_dev *pci,
			      int chip_type,
			      int revision,
			      unsigned int ac97_clock,
			      struct via82xx_modem **r_via)
{
	struct via82xx_modem *chip;
	int err;
        static struct snd_device_ops ops = {
		.dev_free =	snd_via82xx_dev_free,
        };

	if ((err = pci_enable_device(pci)) < 0)
		return err;

	if ((chip = kzalloc(sizeof(*chip), GFP_KERNEL)) == NULL) {
		pci_disable_device(pci);
		return -ENOMEM;
	}

	spin_lock_init(&chip->reg_lock);
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;

	if ((err = pci_request_regions(pci, card->driver)) < 0) {
		kfree(chip);
		pci_disable_device(pci);
		return err;
	}
	chip->port = pci_resource_start(pci, 0);
	if (request_irq(pci->irq, snd_via82xx_interrupt, IRQF_SHARED,
			KBUILD_MODNAME, chip)) {
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_via82xx_free(chip);
		return -EBUSY;
	}
	chip->irq = pci->irq;
	if (ac97_clock >= 8000 && ac97_clock <= 48000)
		chip->ac97_clock = ac97_clock;
	synchronize_irq(chip->irq);

	if ((err = snd_via82xx_chip_init(chip)) < 0) {
		snd_via82xx_free(chip);
		return err;
	}

	if ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) {
		snd_via82xx_free(chip);
		return err;
	}


	pci_set_master(pci);

	*r_via = chip;
	return 0;
}
