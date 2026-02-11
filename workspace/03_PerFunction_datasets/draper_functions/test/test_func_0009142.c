mmc_sdio_detect(struct mmc_host *host)
{
	int err;

	BUG_ON(!host);
	BUG_ON(!host->card);


	if (host->caps & MMC_CAP_POWER_OFF_CARD) {
		err = pm_runtime_get_sync(&host->card->dev);
		if (err < 0) {
			pm_runtime_put_noidle(&host->card->dev);
			goto out;
		}
	}

	mmc_claim_host(host);


	err = _mmc_detect_card_removed(host);

	mmc_release_host(host);


	if (host->caps & MMC_CAP_POWER_OFF_CARD)
		pm_runtime_put_sync(&host->card->dev);

out:
	if (err) {
		mmc_sdio_remove(host);

		mmc_claim_host(host);
		mmc_detach_bus(host);
		mmc_power_off(host);
		mmc_release_host(host);
	}
}
