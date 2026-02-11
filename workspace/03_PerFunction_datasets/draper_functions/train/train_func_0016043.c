mtip_hba_reset(struct driver_data *dd)
{
	unsigned long timeout;


	writel(HOST_RESET, dd->mmio + HOST_CTL);


	readl(dd->mmio + HOST_CTL);


	timeout = jiffies + msecs_to_jiffies(10000);
	do {
		mdelay(10);
		if (test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &dd->dd_flag))
			return -1;

	} while ((readl(dd->mmio + HOST_CTL) & HOST_RESET)
		 && time_before(jiffies, timeout));

	if (readl(dd->mmio + HOST_CTL) & HOST_RESET)
		return -1;

	return 0;
}
