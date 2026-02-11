ci_hdrc_imx_probe(struct platform_device *pdev)
{
	struct ci_hdrc_imx_data *data;
	struct ci_hdrc_platform_data pdata = {
		.name		= dev_name(&pdev->dev),
		.capoffset	= DEF_CAPOFFSET,
	};
	int ret;
	const struct of_device_id *of_id;
	const struct ci_hdrc_imx_platform_flag *imx_platform_flag;

	of_id = of_match_device(ci_hdrc_imx_dt_ids, &pdev->dev);
	if (!of_id)
		return -ENODEV;

	imx_platform_flag = of_id->data;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	platform_set_drvdata(pdev, data);
	data->usbmisc_data = usbmisc_get_init_data(&pdev->dev);
	if (IS_ERR(data->usbmisc_data))
		return PTR_ERR(data->usbmisc_data);

	ret = imx_get_clks(&pdev->dev);
	if (ret)
		return ret;

	ret = imx_prepare_enable_clks(&pdev->dev);
	if (ret)
		return ret;

	data->phy = devm_usb_get_phy_by_phandle(&pdev->dev, "fsl,usbphy", 0);
	if (IS_ERR(data->phy)) {
		ret = PTR_ERR(data->phy);

		if (ret == -ENODEV)
			ret = -EINVAL;
		goto err_clk;
	}

	pdata.usb_phy = data->phy;
	pdata.flags |= imx_platform_flag->flags;
	if (pdata.flags & CI_HDRC_SUPPORTS_RUNTIME_PM)
		data->supports_runtime_pm = true;

	ret = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (ret)
		goto err_clk;

	ret = imx_usbmisc_init(data->usbmisc_data);
	if (ret) {
		dev_err(&pdev->dev, "usbmisc init failed, ret=%d\n", ret);
		goto err_clk;
	}

	data->ci_pdev = ci_hdrc_add_device(&pdev->dev,
				pdev->resource, pdev->num_resources,
				&pdata);
	if (IS_ERR(data->ci_pdev)) {
		ret = PTR_ERR(data->ci_pdev);
		dev_err(&pdev->dev,
			"Can't register ci_hdrc platform device, err=%d\n",
			ret);
		goto err_clk;
	}

	ret = imx_usbmisc_init_post(data->usbmisc_data);
	if (ret) {
		dev_err(&pdev->dev, "usbmisc post failed, ret=%d\n", ret);
		goto disable_device;
	}

	if (data->supports_runtime_pm) {
		pm_runtime_set_active(&pdev->dev);
		pm_runtime_enable(&pdev->dev);
	}

	device_set_wakeup_capable(&pdev->dev, true);

	return 0;

disable_device:
	ci_hdrc_remove_device(data->ci_pdev);
err_clk:
	imx_disable_unprepare_clks(&pdev->dev);
	return ret;
}
