mmc_sdio_suspend(struct mmc_host *host)
{
	mmc_claim_host(host);

	if (mmc_card_keep_power(host) && mmc_card_wake_sdio_irq(host))
		sdio_disable_wide(host->card);

	if (!mmc_card_keep_power(host)) {
		mmc_power_off(host);
	} else if (host->retune_period) {
		mmc_retune_timer_stop(host);
		mmc_retune_needed(host);
	}

	mmc_release_host(host);

	return 0;
}
