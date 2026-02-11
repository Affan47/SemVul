xhci_get_burst_count(struct xhci_hcd *xhci,
		struct urb *urb, unsigned int total_packet_count)
{
	unsigned int max_burst;

	if (xhci->hci_version < 0x100 || urb->dev->speed < USB_SPEED_SUPER)
		return 0;

	max_burst = urb->ep->ss_ep_comp.bMaxBurst;
	return DIV_ROUND_UP(total_packet_count, max_burst + 1) - 1;
}
