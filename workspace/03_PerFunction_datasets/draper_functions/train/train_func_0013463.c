via_sdc_get_ro(struct mmc_host *mmc)
{
	struct via_crdr_mmc_host *host;
	unsigned long flags;
	u16 status;

	host = mmc_priv(mmc);

	spin_lock_irqsave(&host->lock, flags);

	status = readw(host->sdhc_mmiobase + VIA_CRDR_SDSTATUS);

	spin_unlock_irqrestore(&host->lock, flags);

	return !(status & VIA_CRDR_SDSTS_WP);
}
