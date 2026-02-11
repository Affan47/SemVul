mmc_sd_suspend(struct mmc_host *host)
{
	int err;

	err = _mmc_sd_suspend(host);
	if (!err) {
		pm_runtime_disable(&host->card->dev);
		pm_runtime_set_suspended(&host->card->dev);
	}

	return err;
}
