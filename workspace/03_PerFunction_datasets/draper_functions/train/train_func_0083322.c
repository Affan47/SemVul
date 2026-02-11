epout_has_pkt(struct pxa_ep *ep)
{
	if (!is_ep0(ep) && ep->dir_in)
		return -EOPNOTSUPP;
	if (is_ep0(ep))
		return (udc_ep_readl(ep, UDCCSR) & UDCCSR0_OPC);
	return (udc_ep_readl(ep, UDCCSR) & UDCCSR_PC);
}
