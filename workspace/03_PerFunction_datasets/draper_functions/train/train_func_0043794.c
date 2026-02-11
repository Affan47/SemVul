tpm_stm_spi_request_resources(struct spi_device *dev,
					 struct st33zp24_spi_phy *phy)
{
	struct st33zp24_platform_data *pdata;
	int ret;

	pdata = dev->dev.platform_data;
	if (!pdata) {
		dev_err(&dev->dev, "No platform data\n");
		return -ENODEV;
	}


	phy->io_lpcpd = pdata->io_lpcpd;

	if (gpio_is_valid(pdata->io_lpcpd)) {
		ret = devm_gpio_request_one(&dev->dev,
				pdata->io_lpcpd, GPIOF_OUT_INIT_HIGH,
				"TPM IO_LPCPD");
		if (ret) {
			dev_err(&dev->dev, "%s : reset gpio_request failed\n",
				__FILE__);
			return ret;
		}
	}

	return 0;
}
