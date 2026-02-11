dwc2_resume(struct device *dev)
{
	struct dwc2_hsotg *dwc2 = dev_get_drvdata(dev);
	int ret = 0;

	if (dwc2->ll_hw_enabled) {
		ret = __dwc2_lowlevel_hw_enable(dwc2);
		if (ret)
			return ret;
	}

	if (dwc2_is_device_mode(dwc2))
		ret = dwc2_hsotg_resume(dwc2);

	return ret;
}
