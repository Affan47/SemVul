ptp_pch_settime(struct ptp_clock_info *ptp,
			   const struct timespec64 *ts)
{
	u64 ns;
	unsigned long flags;
	struct pch_dev *pch_dev = container_of(ptp, struct pch_dev, caps);
	struct pch_ts_regs __iomem *regs = pch_dev->regs;

	ns = ts->tv_sec * 1000000000ULL;
	ns += ts->tv_nsec;

	spin_lock_irqsave(&pch_dev->register_lock, flags);
	pch_systime_write(regs, ns);
	spin_unlock_irqrestore(&pch_dev->register_lock, flags);

	return 0;
}
