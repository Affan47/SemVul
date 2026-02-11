bfa_ioc_ct_firmware_unlock(struct bfa_ioc_s *ioc)
{
	u32 usecnt;


	bfa_ioc_sem_get(ioc->ioc_regs.ioc_usage_sem_reg);
	usecnt = readl(ioc->ioc_regs.ioc_usage_reg);
	WARN_ON(usecnt <= 0);

	usecnt--;
	writel(usecnt, ioc->ioc_regs.ioc_usage_reg);
	bfa_trc(ioc, usecnt);

	readl(ioc->ioc_regs.ioc_usage_sem_reg);
	writel(1, ioc->ioc_regs.ioc_usage_sem_reg);
}
