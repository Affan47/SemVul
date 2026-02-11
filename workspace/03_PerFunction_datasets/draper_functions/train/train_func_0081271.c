xhci_check_bw_drop_ep_streams(struct xhci_hcd *xhci,
	struct xhci_virt_device *vdev, int i)
{
	struct xhci_virt_ep *ep = &vdev->eps[i];

	if (ep->ep_state & EP_HAS_STREAMS) {
		xhci_warn(xhci, "WARN: endpoint 0x%02x has streams on set_interface, freeing streams.\n",
				xhci_get_endpoint_address(i));
		xhci_free_stream_info(xhci, ep->stream_info);
		ep->stream_info = NULL;
		ep->ep_state &= ~EP_HAS_STREAMS;
	}
}
