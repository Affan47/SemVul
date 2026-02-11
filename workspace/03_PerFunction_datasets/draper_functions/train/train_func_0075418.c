sun4i_spi_runtime_resume(struct device *dev)
{
	struct spi_master *master = dev_get_drvdata(dev);
	struct sun4i_spi *sspi = spi_master_get_devdata(master);
	int ret;

	ret = clk_prepare_enable(sspi->hclk);
	if (ret) {
		dev_err(dev, "Couldn't enable AHB clock\n");
		goto out;
	}

	ret = clk_prepare_enable(sspi->mclk);
	if (ret) {
		dev_err(dev, "Couldn't enable module clock\n");
		goto err;
	}

	sun4i_spi_write(sspi, SUN4I_CTL_REG,
			SUN4I_CTL_ENABLE | SUN4I_CTL_MASTER | SUN4I_CTL_TP);

	return 0;

err:
	clk_disable_unprepare(sspi->hclk);
out:
	return ret;
}
