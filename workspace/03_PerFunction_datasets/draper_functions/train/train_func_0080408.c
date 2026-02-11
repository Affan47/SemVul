sirf_usp_pcm_suspend(struct device *dev)
{
	struct sirf_usp *usp = dev_get_drvdata(dev);

	if (!pm_runtime_status_suspended(dev)) {
		regmap_read(usp->regmap, USP_MODE1, &usp->mode1_reg);
		regmap_read(usp->regmap, USP_MODE2, &usp->mode2_reg);
		sirf_usp_pcm_runtime_suspend(dev);
	}
	return 0;
}
