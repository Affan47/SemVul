pch_udc_ep_set_stall(struct pch_udc_ep *ep)
{
	if (ep->in) {
		pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_F);
		pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_S);
	} else {
		pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_S);
	}
}
