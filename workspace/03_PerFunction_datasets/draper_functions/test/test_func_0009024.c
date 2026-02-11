wm8350_register_regulator(struct wm8350 *wm8350, int reg,
			      struct regulator_init_data *initdata)
{
	struct platform_device *pdev;
	int ret;
	if (reg < 0 || reg >= NUM_WM8350_REGULATORS)
		return -EINVAL;

	if (wm8350->pmic.pdev[reg])
		return -EBUSY;

	if (reg >= WM8350_DCDC_1 && reg <= WM8350_DCDC_6 &&
	    reg > wm8350->pmic.max_dcdc)
		return -ENODEV;
	if (reg >= WM8350_ISINK_A && reg <= WM8350_ISINK_B &&
	    reg > wm8350->pmic.max_isink)
		return -ENODEV;

	pdev = platform_device_alloc("wm8350-regulator", reg);
	if (!pdev)
		return -ENOMEM;

	wm8350->pmic.pdev[reg] = pdev;

	initdata->driver_data = wm8350;

	pdev->dev.platform_data = initdata;
	pdev->dev.parent = wm8350->dev;
	platform_set_drvdata(pdev, wm8350);

	ret = platform_device_add(pdev);

	if (ret != 0) {
		dev_err(wm8350->dev, "Failed to register regulator %d: %d\n",
			reg, ret);
		platform_device_put(pdev);
		wm8350->pmic.pdev[reg] = NULL;
	}

	return ret;
}
