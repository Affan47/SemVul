ns83820_set_multicast(struct nic *nic __unused)
{
	u8 *rfcr = ns->base + RFCR;
	u32 and_mask = 0xffffffff;
	u32 or_mask = 0;
	u32 val;


	and_mask &= ~(RFCR_AAU | RFCR_AAM);
	or_mask |= RFCR_AAM;
	val = (readl(rfcr) & and_mask) | or_mask;

	writel(val & ~RFCR_RFEN, rfcr);
	writel(val, rfcr);

}
