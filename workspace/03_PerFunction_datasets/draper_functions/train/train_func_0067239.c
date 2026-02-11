UDC_QUEUE_CNAK(struct udc_ep *ep, unsigned num)
{
	if (readl(&ep->regs->ctl) & AMD_BIT(UDC_EPCTL_NAK)) {
		DBG(ep->dev, "NAK could not be cleared for ep%d\n", num);
		cnak_pending |= 1 << (num);
		ep->naking = 1;
	} else
		cnak_pending = cnak_pending & (~(1 << (num)));
}
