sm501_misc_control(struct device *dev,
		       unsigned long set, unsigned long clear)
{
	struct sm501_devdata *sm = dev_get_drvdata(dev);
	unsigned long misc;
	unsigned long save;
	unsigned long to;

	spin_lock_irqsave(&sm->reg_lock, save);

	misc = smc501_readl(sm->regs + SM501_MISC_CONTROL);
	to = (misc & ~clear) | set;

	if (to != misc) {
		smc501_writel(to, sm->regs + SM501_MISC_CONTROL);
		sm501_sync_regs(sm);

		dev_dbg(sm->dev, "MISC_CONTROL %08lx\n", misc);
	}

	spin_unlock_irqrestore(&sm->reg_lock, save);
	return to;
}
