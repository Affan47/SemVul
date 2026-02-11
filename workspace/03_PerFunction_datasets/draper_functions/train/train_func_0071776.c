xhci_check_streams_endpoint(struct xhci_hcd *xhci,
		struct usb_device *udev, struct usb_host_endpoint *ep,
		unsigned int slot_id)
{
	int ret;
	unsigned int ep_index;
	unsigned int ep_state;

	if (!ep)
		return -EINVAL;
	ret = xhci_check_args(xhci_to_hcd(xhci), udev, ep, 1, true, __func__);
	if (ret <= 0)
		return -EINVAL;
	if (usb_ss_max_streams(&ep->ss_ep_comp) == 0) {
		xhci_warn(xhci, "WARN: SuperSpeed Endpoint Companion"
				" descriptor for ep 0x%x does not support streams\n",
				ep->desc.bEndpointAddress);
		return -EINVAL;
	}

	ep_index = xhci_get_endpoint_index(&ep->desc);
	ep_state = xhci->devs[slot_id]->eps[ep_index].ep_state;
	if (ep_state & EP_HAS_STREAMS ||
			ep_state & EP_GETTING_STREAMS) {
		xhci_warn(xhci, "WARN: SuperSpeed bulk endpoint 0x%x "
				"already has streams set up.\n",
				ep->desc.bEndpointAddress);
		xhci_warn(xhci, "Send email to xHCI maintainer and ask for "
				"dynamic stream context array reallocation.\n");
		return -EINVAL;
	}
	if (!list_empty(&xhci->devs[slot_id]->eps[ep_index].ring->td_list)) {
		xhci_warn(xhci, "Cannot setup streams for SuperSpeed bulk "
				"endpoint 0x%x; URBs are pending.\n",
				ep->desc.bEndpointAddress);
		return -EINVAL;
	}
	return 0;
}
