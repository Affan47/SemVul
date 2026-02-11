dwc2_hsotg_stall_ep0(struct dwc2_hsotg *hsotg)
{
	struct dwc2_hsotg_ep *ep0 = hsotg->eps_out[0];
	u32 reg;
	u32 ctrl;

	dev_dbg(hsotg->dev, "ep0 stall (dir=%d)\n", ep0->dir_in);
	reg = (ep0->dir_in) ? DIEPCTL0 : DOEPCTL0;


	ctrl = dwc2_readl(hsotg->regs + reg);
	ctrl |= DXEPCTL_STALL;
	ctrl |= DXEPCTL_CNAK;
	dwc2_writel(ctrl, hsotg->regs + reg);

	dev_dbg(hsotg->dev,
		"written DXEPCTL=0x%08x to %08x (DXEPCTL=0x%08x)\n",
		ctrl, reg, dwc2_readl(hsotg->regs + reg));


	 dwc2_hsotg_enqueue_setup(hsotg);
}
