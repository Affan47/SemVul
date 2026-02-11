pch_udc_ep_disable(struct pch_udc_ep *ep)
{
	if (ep->in) {

		pch_udc_ep_writel(ep, UDC_EPCTL_F, UDC_EPCTL_ADDR);

		pch_udc_ep_writel(ep, UDC_EPCTL_SNAK, UDC_EPCTL_ADDR);
		pch_udc_ep_bit_set(ep, UDC_EPSTS_ADDR, UDC_EPSTS_IN);
	} else {

		pch_udc_ep_writel(ep, UDC_EPCTL_SNAK, UDC_EPCTL_ADDR);
	}

	pch_udc_ep_writel(ep, 0, UDC_DESPTR_ADDR);
}
