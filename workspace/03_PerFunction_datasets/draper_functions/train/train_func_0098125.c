dwc2_hsotg_program_zlp(struct dwc2_hsotg *hsotg,
					struct dwc2_hsotg_ep *hs_ep)
{
	u32 ctrl;
	u8 index = hs_ep->index;
	u32 epctl_reg = hs_ep->dir_in ? DIEPCTL(index) : DOEPCTL(index);
	u32 epsiz_reg = hs_ep->dir_in ? DIEPTSIZ(index) : DOEPTSIZ(index);

	if (hs_ep->dir_in)
		dev_dbg(hsotg->dev, "Sending zero-length packet on ep%d\n",
									index);
	else
		dev_dbg(hsotg->dev, "Receiving zero-length packet on ep%d\n",
									index);

	dwc2_writel(DXEPTSIZ_MC(1) | DXEPTSIZ_PKTCNT(1) |
		    DXEPTSIZ_XFERSIZE(0), hsotg->regs +
		    epsiz_reg);

	ctrl = dwc2_readl(hsotg->regs + epctl_reg);
	ctrl |= DXEPCTL_CNAK;
	ctrl |= DXEPCTL_EPENA;
	ctrl |= DXEPCTL_USBACTEP;
	dwc2_writel(ctrl, hsotg->regs + epctl_reg);
}
