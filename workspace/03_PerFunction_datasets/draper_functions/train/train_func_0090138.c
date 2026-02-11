exynos_adc_suspend(struct device *dev)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct exynos_adc *info = iio_priv(indio_dev);

	if (info->data->exit_hw)
		info->data->exit_hw(info);
	exynos_adc_disable_clk(info);
	regulator_disable(info->vdd);

	return 0;
}
