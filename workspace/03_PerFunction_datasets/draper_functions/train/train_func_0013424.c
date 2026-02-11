omap_hsmmc_suspend(struct device *dev)
{
	struct omap_hsmmc_host *host = dev_get_drvdata(dev);

	if (!host)
		return 0;

	pm_runtime_get_sync(host->dev);

	if (!(host->mmc->pm_flags & MMC_PM_KEEP_POWER)) {
		OMAP_HSMMC_WRITE(host->base, ISE, 0);
		OMAP_HSMMC_WRITE(host->base, IE, 0);
		OMAP_HSMMC_WRITE(host->base, STAT, STAT_CLEAR);
		OMAP_HSMMC_WRITE(host->base, HCTL,
				OMAP_HSMMC_READ(host->base, HCTL) & ~SDBP);
	}

	if (host->dbclk)
		clk_disable_unprepare(host->dbclk);

	pm_runtime_put_sync(host->dev);
	return 0;
}
