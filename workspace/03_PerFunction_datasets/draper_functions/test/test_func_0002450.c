stmmac_adjust_systime(void __iomem *ioaddr, u32 sec, u32 nsec,
				 int add_sub)
{
	u32 value;
	int limit;

	writel(sec, ioaddr + PTP_STSUR);
	writel(((add_sub << PTP_STNSUR_ADDSUB_SHIFT) | nsec),
		ioaddr + PTP_STNSUR);

	value = readl(ioaddr + PTP_TCR);
	value |= PTP_TCR_TSUPDT;
	writel(value, ioaddr + PTP_TCR);


	limit = 10;
	while (limit--) {
		if (!(readl(ioaddr + PTP_TCR) & PTP_TCR_TSUPDT))
			break;
		mdelay(10);
	}
	if (limit < 0)
		return -EBUSY;

	return 0;
}
