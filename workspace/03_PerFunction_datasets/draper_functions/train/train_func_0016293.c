sdhci_pxav3_runtime_suspend(struct device *dev)
{
	struct sdhci_host *host = dev_get_drvdata(dev);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_pxa *pxa = pltfm_host->priv;
	int ret;

	ret = sdhci_runtime_suspend_host(host);
	if (ret)
		return ret;

	clk_disable_unprepare(pxa->clk_io);
	if (!IS_ERR(pxa->clk_core))
		clk_disable_unprepare(pxa->clk_core);

	return 0;
}
