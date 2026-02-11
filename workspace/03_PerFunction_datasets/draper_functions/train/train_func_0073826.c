azx_resume(struct device *dev)
{
	struct pci_dev *pci = to_pci_dev(dev);
	struct snd_card *card = dev_get_drvdata(dev);
	struct azx *chip;
	struct hda_intel *hda;
	struct hdac_bus *bus;

	if (!card)
		return 0;

	chip = card->private_data;
	hda = container_of(chip, struct hda_intel, chip);
	bus = azx_bus(chip);
	if (chip->disabled || hda->init_failed || !chip->running)
		return 0;

	if (chip->driver_caps & AZX_DCAPS_I915_POWERWELL) {
		snd_hdac_display_power(bus, true);
		if (hda->need_i915_power)
			haswell_set_bclk(hda);
	}

	if (chip->msi)
		if (pci_enable_msi(pci) < 0)
			chip->msi = 0;
	if (azx_acquire_irq(chip, 1) < 0)
		return -EIO;
	azx_init_pci(chip);

	hda_intel_init_chip(chip, true);


	if ((chip->driver_caps & AZX_DCAPS_I915_POWERWELL) &&
	    !hda->need_i915_power)
		snd_hdac_display_power(bus, false);

	snd_power_change_state(card, SNDRV_CTL_POWER_D0);

	trace_azx_resume(chip);
	return 0;
}
