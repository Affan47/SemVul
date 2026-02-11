of_mpc8xxx_spi_probe(struct platform_device *ofdev)
{
	struct device *dev = &ofdev->dev;
	struct device_node *np = ofdev->dev.of_node;
	struct mpc8xxx_spi_probe_info *pinfo;
	struct fsl_spi_platform_data *pdata;
	const void *prop;
	int ret = -ENOMEM;

	pinfo = devm_kzalloc(&ofdev->dev, sizeof(*pinfo), GFP_KERNEL);
	if (!pinfo)
		return ret;

	pdata = &pinfo->pdata;
	dev->platform_data = pdata;


	pdata->bus_num = -1;

#ifdef CONFIG_FSL_SOC

	pdata->sysclk = get_brgfreq();
	if (pdata->sysclk == -1) {
		pdata->sysclk = fsl_get_sys_freq();
		if (pdata->sysclk == -1)
			return -ENODEV;
	}
#else
	ret = of_property_read_u32(np, "clock-frequency", &pdata->sysclk);
	if (ret)
		return ret;
#endif

	prop = of_get_property(np, "mode", NULL);
	if (prop && !strcmp(prop, "cpu-qe"))
		pdata->flags = SPI_QE_CPU_MODE;
	else if (prop && !strcmp(prop, "qe"))
		pdata->flags = SPI_CPM_MODE | SPI_QE;
	else if (of_device_is_compatible(np, "fsl,cpm2-spi"))
		pdata->flags = SPI_CPM_MODE | SPI_CPM2;
	else if (of_device_is_compatible(np, "fsl,cpm1-spi"))
		pdata->flags = SPI_CPM_MODE | SPI_CPM1;

	return 0;
}
