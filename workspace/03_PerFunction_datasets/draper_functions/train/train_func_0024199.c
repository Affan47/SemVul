azx_suspend(struct device *dev)
{
	struct snd_card *card = dev_get_drvdata(dev);
	struct azx *chip;
	struct hda_intel *hda;
	struct hdac_bus *bus;

	if (!card)
		return 0;

	chip = card->private_data;
	hda = container_of(chip, struct hda_intel, chip);
	if (chip->disabled || hda->init_failed || !chip->running)
		return 0;

	bus = azx_bus(chip);
	snd_power_change_state(card, SNDRV_CTL_POWER_D3hot);
	azx_clear_irq_pending(chip);
	azx_stop_chip(chip);
	azx_enter_link_reset(chip);
	if (bus->irq >= 0) {
		free_irq(bus->irq, chip);
		bus->irq = -1;
	}

	if (chip->msi)
		pci_disable_msi(chip->pci);
	if (chip->driver_caps & AZX_DCAPS_I915_POWERWELL
		&& hda->need_i915_power)
		snd_hdac_display_power(bus, false);

	trace_azx_suspend(chip);
	return 0;
}
