dwc2_wakeup_detected(unsigned long data)
{
	struct dwc2_hsotg *hsotg = (struct dwc2_hsotg *)data;
	u32 hprt0;

	dev_dbg(hsotg->dev, "%s()\n", __func__);


	hprt0 = dwc2_read_hprt0(hsotg);
	dev_dbg(hsotg->dev, "Resume: HPRT0=%0x\n", hprt0);
	hprt0 &= ~HPRT0_RES;
	dwc2_writel(hprt0, hsotg->regs + HPRT0);
	dev_dbg(hsotg->dev, "Clear Resume: HPRT0=%0x\n",
		dwc2_readl(hsotg->regs + HPRT0));

	dwc2_hcd_rem_wakeup(hsotg);
	hsotg->bus_suspended = 0;


	hsotg->lx_state = DWC2_L0;
}
