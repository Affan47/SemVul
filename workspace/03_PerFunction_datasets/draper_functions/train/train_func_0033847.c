mv_write_cached_reg(void __iomem *addr, u32 *old, u32 new)
{
	if (new != *old) {
		unsigned long laddr;
		*old = new;


		laddr = (long)addr & 0xffff;
		if (laddr >= 0x300 && laddr <= 0x33c) {
			laddr &= 0x000f;
			if (laddr == 0x4 || laddr == 0xc) {
				writelfl(new, addr);
				return;
			}
		}
		writel(new, addr);
	}
}
