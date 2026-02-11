dw_i2c_plat_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct dw_i2c_dev *i_dev = platform_get_drvdata(pdev);

	i2c_dw_plat_prepare_clk(i_dev, true);

	if (!i_dev->pm_runtime_disabled)
		i2c_dw_init(i_dev);

	return 0;
}
