skd_soft_reset(struct skd_device *skdev)
{
	u32 val;

	val = SKD_READL(skdev, FIT_CONTROL);
	val |= (FIT_CR_SOFT_RESET);
	pr_debug("%s:%s:%d control=0x%x\n",
		 skdev->name, __func__, __LINE__, val);
	SKD_WRITEL(skdev, val, FIT_CONTROL);
}
