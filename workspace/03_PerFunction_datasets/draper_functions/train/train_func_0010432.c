meson_spifc_probe(struct platform_device *pdev)
{
	struct spi_master *master;
	struct meson_spifc *spifc;
	struct resource *res;
	void __iomem *base;
	unsigned int rate;
	int ret = 0;

	master = spi_alloc_master(&pdev->dev, sizeof(struct meson_spifc));
	if (!master)
		return -ENOMEM;

	platform_set_drvdata(pdev, master);

	spifc = spi_master_get_devdata(master);
	spifc->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(spifc->dev, res);
	if (IS_ERR(base)) {
		ret = PTR_ERR(base);
		goto out_err;
	}

	spifc->regmap = devm_regmap_init_mmio(spifc->dev, base,
					      &spifc_regmap_config);
	if (IS_ERR(spifc->regmap)) {
		ret = PTR_ERR(spifc->regmap);
		goto out_err;
	}

	spifc->clk = devm_clk_get(spifc->dev, NULL);
	if (IS_ERR(spifc->clk)) {
		dev_err(spifc->dev, "missing clock\n");
		ret = PTR_ERR(spifc->clk);
		goto out_err;
	}

	ret = clk_prepare_enable(spifc->clk);
	if (ret) {
		dev_err(spifc->dev, "can't prepare clock\n");
		goto out_err;
	}

	rate = clk_get_rate(spifc->clk);

	master->num_chipselect = 1;
	master->dev.of_node = pdev->dev.of_node;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->auto_runtime_pm = true;
	master->transfer_one = meson_spifc_transfer_one;
	master->min_speed_hz = rate >> 6;
	master->max_speed_hz = rate >> 1;

	meson_spifc_hw_init(spifc);

	pm_runtime_set_active(spifc->dev);
	pm_runtime_enable(spifc->dev);

	ret = devm_spi_register_master(spifc->dev, master);
	if (ret) {
		dev_err(spifc->dev, "failed to register spi master\n");
		goto out_clk;
	}

	return 0;
out_clk:
	clk_disable_unprepare(spifc->clk);
out_err:
	spi_master_put(master);
	return ret;
}
