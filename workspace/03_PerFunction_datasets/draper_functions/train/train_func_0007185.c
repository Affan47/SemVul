sdhci_pci_hw_reset(struct sdhci_host *host)
{
	struct sdhci_pci_slot *slot = sdhci_priv(host);

	if (slot->hw_reset)
		slot->hw_reset(host);
}
