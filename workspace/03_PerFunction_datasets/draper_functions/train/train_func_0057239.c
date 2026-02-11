async_resume_noirq(void *data, async_cookie_t cookie)
{
	struct device *dev = (struct device *)data;
	int error;

	error = device_resume_noirq(dev, pm_transition, true);
	if (error)
		pm_dev_err(dev, pm_transition, " async", error);

	put_device(dev);
}
