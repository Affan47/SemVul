bdisp_resume(struct device *dev)
{
	struct bdisp_dev *bdisp = dev_get_drvdata(dev);
	unsigned long flags;
	int opened;

	spin_lock_irqsave(&bdisp->slock, flags);
	opened = test_bit(ST_M2M_OPEN, &bdisp->state);
	spin_unlock_irqrestore(&bdisp->slock, flags);

	if (!opened)
		return 0;

	if (!pm_runtime_suspended(dev))
		return bdisp_runtime_resume(dev);

	return 0;
}
