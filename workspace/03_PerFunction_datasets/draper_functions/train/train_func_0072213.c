sdhci_enable_sdio_irq_nolock(struct sdhci_host *host, int enable)
{
	if (!(host->flags & SDHCI_DEVICE_DEAD)) {
		if (enable)
			host->ier |= SDHCI_INT_CARD_INT;
		else
			host->ier &= ~SDHCI_INT_CARD_INT;

		sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
		sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
		mmiowb();
	}
}
