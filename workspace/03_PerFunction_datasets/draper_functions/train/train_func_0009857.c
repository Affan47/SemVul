snd_via82xx_create(struct snd_card *card,
			      struct pci_dev *pci,
			      int chip_type,
			      int revision,
			      unsigned int ac97_clock,
			      struct via82xx **r_via)
{
	struct via82xx *chip;
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

	chip->chip_type = chip_type;
	chip->revision = revision;

	spin_lock_init(&chip->reg_lock);
	spin_lock_init(&chip->rates[0].lock);
	spin_lock_init(&chip->rates[1].lock);
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;

	pci_read_config_byte(pci, VIA_FUNC_ENABLE, &chip->old_legacy);
	pci_read_config_byte(pci, VIA_PNP_CONTROL, &chip->old_legacy_cfg);
	pci_write_config_byte(chip->pci, VIA_FUNC_ENABLE,
			      chip->old_legacy & ~(VIA_FUNC_ENABLE_SB|VIA_FUNC_ENABLE_FM));

	if ((err = pci_request_regions(pci, card->driver)) < 0) {
		kfree(chip);
		pci_disable_device(pci);
		return err;
	}
	chip->port = pci_resource_start(pci, 0);
	if (request_irq(pci->irq,
			chip_type == TYPE_VIA8233 ?
			snd_via8233_interrupt :	snd_via686_interrupt,
			IRQF_SHARED,
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
