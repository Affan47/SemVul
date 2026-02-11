ci_resume(struct device *dev)
{
	struct ci_hdrc *ci = dev_get_drvdata(dev);
	int ret;

	if (device_may_wakeup(dev))
		disable_irq_wake(ci->irq);

	ret = ci_controller_resume(dev);
	if (ret)
		return ret;

	if (ci->supports_runtime_pm) {
		pm_runtime_disable(dev);
		pm_runtime_set_active(dev);
		pm_runtime_enable(dev);
	}

	return ret;
}
