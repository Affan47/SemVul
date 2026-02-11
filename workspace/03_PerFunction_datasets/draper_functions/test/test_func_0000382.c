hsw_pcm_runtime_suspend(struct device *dev)
{
	struct hsw_priv_data *pdata = dev_get_drvdata(dev);
	struct sst_hsw *hsw = pdata->hsw;
	int ret;

	if (pdata->pm_state >= HSW_PM_STATE_RTD3)
		return 0;


	if (sst_hsw_is_module_active(hsw, SST_HSW_MODULE_WAVES)) {
		ret = sst_hsw_module_disable(hsw, SST_HSW_MODULE_WAVES, 0);
		if (ret < 0)
			return ret;
		sst_hsw_set_module_enabled_rtd3(hsw, SST_HSW_MODULE_WAVES);
	}
	hsw_pcm_suspend(dev);
	pdata->pm_state = HSW_PM_STATE_RTD3;

	return 0;
}
