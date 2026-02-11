ep_is_empty(struct pxa_ep *ep)
{
	int ret;

	if (!is_ep0(ep) && ep->dir_in)
		return -EOPNOTSUPP;
	if (is_ep0(ep))
		ret = !(udc_ep_readl(ep, UDCCSR) & UDCCSR0_RNE);
	else
		ret = !(udc_ep_readl(ep, UDCCSR) & UDCCSR_BNE);
	return ret;
}
