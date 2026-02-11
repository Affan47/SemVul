via_probe(struct sdhci_pci_chip *chip)
{
	if (chip->pdev->revision == 0x10)
		chip->quirks |= SDHCI_QUIRK_DELAY_AFTER_POWER;

	return 0;
}
