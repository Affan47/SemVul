gr_fifo_status(struct usb_ep *_ep)
{
	struct gr_ep *ep;
	u32 epstat;
	u32 bytes = 0;

	if (!_ep)
		return -ENODEV;
	ep = container_of(_ep, struct gr_ep, ep);

	epstat = gr_read32(&ep->regs->epstat);

	if (epstat & GR_EPSTAT_B0)
		bytes += (epstat & GR_EPSTAT_B0CNT_MASK) >> GR_EPSTAT_B0CNT_POS;
	if (epstat & GR_EPSTAT_B1)
		bytes += (epstat & GR_EPSTAT_B1CNT_MASK) >> GR_EPSTAT_B1CNT_POS;

	return bytes;
}
