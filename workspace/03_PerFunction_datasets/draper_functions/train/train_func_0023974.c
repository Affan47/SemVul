snd_via82xx_free(struct via82xx_modem *chip)
{
	unsigned int i;

	if (chip->irq < 0)
		goto __end_hw;

	for (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channel_reset(chip, &chip->devs[i]);

      __end_hw:
	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kfree(chip);
	return 0;
}
