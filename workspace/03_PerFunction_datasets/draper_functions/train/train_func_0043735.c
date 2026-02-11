spi_gpio_probe_dt(struct platform_device *pdev)
{
	int ret;
	u32 tmp;
	struct spi_gpio_platform_data	*pdata;
	struct device_node *np = pdev->dev.of_node;
	const struct of_device_id *of_id =
			of_match_device(spi_gpio_dt_ids, &pdev->dev);

	if (!of_id)
		return 0;

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	ret = of_get_named_gpio(np, "gpio-sck", 0);
	if (ret < 0) {
		dev_err(&pdev->dev, "gpio-sck property not found\n");
		goto error_free;
	}
	pdata->sck = ret;

	ret = of_get_named_gpio(np, "gpio-miso", 0);
	if (ret < 0) {
		dev_info(&pdev->dev, "gpio-miso property not found, switching to no-rx mode\n");
		pdata->miso = SPI_GPIO_NO_MISO;
	} else
		pdata->miso = ret;

	ret = of_get_named_gpio(np, "gpio-mosi", 0);
	if (ret < 0) {
		dev_info(&pdev->dev, "gpio-mosi property not found, switching to no-tx mode\n");
		pdata->mosi = SPI_GPIO_NO_MOSI;
	} else
		pdata->mosi = ret;

	ret = of_property_read_u32(np, "num-chipselects", &tmp);
	if (ret < 0) {
		dev_err(&pdev->dev, "num-chipselects property not found\n");
		goto error_free;
	}

	pdata->num_chipselect = tmp;
	pdev->dev.platform_data = pdata;

	return 1;

error_free:
	devm_kfree(&pdev->dev, pdata);
	return ret;
}
