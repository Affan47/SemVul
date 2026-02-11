r592_clear_reg_mask(struct r592_device *dev,
						int address, u32 mask)
{
	u32 reg = readl(dev->mmio + address);
	dbg_reg("reg #%02d &= 0x%08x (old = 0x%08x, mask = 0x%08x)",
						address, ~mask, reg, mask);
	writel(reg & ~mask, dev->mmio + address);
}
