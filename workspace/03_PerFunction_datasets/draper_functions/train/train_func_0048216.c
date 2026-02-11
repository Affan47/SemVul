gsc_runtime_suspend(struct device *dev)
{
	struct gsc_dev *gsc = dev_get_drvdata(dev);
	int ret = 0;

	ret = gsc_m2m_suspend(gsc);
	if (!ret)
		clk_disable(gsc->clock);

	pr_debug("gsc%d: state: 0x%lx", gsc->id, gsc->state);
	return ret;
}
