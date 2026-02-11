m48t59_nvram_write(struct file *filp, struct kobject *kobj,
				struct bin_attribute *bin_attr,
				char *buf, loff_t pos, size_t size)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	struct platform_device *pdev = to_platform_device(dev);
	struct m48t59_plat_data *pdata = dev_get_platdata(&pdev->dev);
	struct m48t59_private *m48t59 = platform_get_drvdata(pdev);
	ssize_t cnt = 0;
	unsigned long flags;

	spin_lock_irqsave(&m48t59->lock, flags);

	for (; cnt < size; cnt++)
		M48T59_WRITE(*buf++, cnt);

	spin_unlock_irqrestore(&m48t59->lock, flags);

	return cnt;
}
