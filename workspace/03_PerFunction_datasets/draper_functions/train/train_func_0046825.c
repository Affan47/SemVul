mtk_spi_resume(struct device *dev)
{
	int ret;
	struct spi_master *master = dev_get_drvdata(dev);
	struct mtk_spi *mdata = spi_master_get_devdata(master);

	if (!pm_runtime_suspended(dev)) {
		ret = clk_prepare_enable(mdata->spi_clk);
		if (ret < 0) {
			dev_err(dev, "failed to enable spi_clk (%d)\n", ret);
			return ret;
		}
	}

	ret = spi_master_resume(master);
	if (ret < 0)
		clk_disable_unprepare(mdata->spi_clk);

	return ret;
}
