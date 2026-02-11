pch_udc_ep_clear_nak(struct pch_udc_ep *ep)
{
	unsigned int loopcnt = 0;
	struct pch_udc_dev *dev = ep->dev;

	if (!(pch_udc_ep_readl(ep, UDC_EPCTL_ADDR) & UDC_EPCTL_NAK))
		return;
	if (!ep->in) {
		loopcnt = 10000;
		while (!(pch_udc_read_ep_status(ep) & UDC_EPSTS_MRXFIFO_EMP) &&
			--loopcnt)
			udelay(5);
		if (!loopcnt)
			dev_err(&dev->pdev->dev, "%s: RxFIFO not Empty\n",
				__func__);
	}
	loopcnt = 10000;
	while ((pch_udc_read_ep_control(ep) & UDC_EPCTL_NAK) && --loopcnt) {
		pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_CNAK);
		udelay(5);
	}
	if (!loopcnt)
		dev_err(&dev->pdev->dev, "%s: Clear NAK not set for ep%d%s\n",
			__func__, ep->num, (ep->in ? "in" : "out"));
}
