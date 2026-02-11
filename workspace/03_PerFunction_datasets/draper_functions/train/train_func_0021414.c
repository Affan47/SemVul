tusb_set_clock_source(struct musb *musb, unsigned mode)
{
	void __iomem	*tbase = musb->ctrl_base;
	u32		reg;

	reg = musb_readl(tbase, TUSB_PRCM_CONF);
	reg &= ~TUSB_PRCM_CONF_SYS_CLKSEL(0x3);


	if (mode > 0)
		reg |= TUSB_PRCM_CONF_SYS_CLKSEL(mode & 0x3);

	musb_writel(tbase, TUSB_PRCM_CONF, reg);


}
