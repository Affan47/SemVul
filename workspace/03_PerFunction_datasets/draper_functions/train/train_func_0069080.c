ptp_pch_adjfreq(struct ptp_clock_info *ptp, s32 ppb)
{
	u64 adj;
	u32 diff, addend;
	int neg_adj = 0;
	struct pch_dev *pch_dev = container_of(ptp, struct pch_dev, caps);
	struct pch_ts_regs __iomem *regs = pch_dev->regs;

	if (ppb < 0) {
		neg_adj = 1;
		ppb = -ppb;
	}
	addend = DEFAULT_ADDEND;
	adj = addend;
	adj *= ppb;
	diff = div_u64(adj, 1000000000ULL);

	addend = neg_adj ? addend - diff : addend + diff;

	iowrite32(addend, &regs->addend);

	return 0;
}
