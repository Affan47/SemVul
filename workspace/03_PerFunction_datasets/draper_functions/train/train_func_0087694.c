bcm63xx_hsspi_set_cs(struct bcm63xx_hsspi *bs, unsigned cs,
				 bool active)
{
	u32 reg;

	mutex_lock(&bs->bus_mutex);
	reg = __raw_readl(bs->regs + HSSPI_GLOBAL_CTRL_REG);

	reg &= ~BIT(cs);
	if (active == !(bs->cs_polarity & BIT(cs)))
		reg |= BIT(cs);

	__raw_writel(reg, bs->regs + HSSPI_GLOBAL_CTRL_REG);
	mutex_unlock(&bs->bus_mutex);
}
