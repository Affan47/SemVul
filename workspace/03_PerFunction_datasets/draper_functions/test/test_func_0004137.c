dwc2_hsotg_txfifo_flush(struct dwc2_hsotg *hsotg, unsigned int idx)
{
	int timeout;
	int val;

	dwc2_writel(GRSTCTL_TXFNUM(idx) | GRSTCTL_TXFFLSH,
		    hsotg->regs + GRSTCTL);


	timeout = 100;

	while (1) {
		val = dwc2_readl(hsotg->regs + GRSTCTL);

		if ((val & (GRSTCTL_TXFFLSH)) == 0)
			break;

		if (--timeout == 0) {
			dev_err(hsotg->dev,
				"%s: timeout flushing fifo (GRSTCTL=%08x)\n",
				__func__, val);
			break;
		}

		udelay(1);
	}
}
