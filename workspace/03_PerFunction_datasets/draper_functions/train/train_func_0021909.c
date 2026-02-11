xhci_get_max_esit_payload(struct usb_device *udev,
		struct usb_host_endpoint *ep)
{
	int max_burst;
	int max_packet;


	if (usb_endpoint_xfer_control(&ep->desc) ||
			usb_endpoint_xfer_bulk(&ep->desc))
		return 0;


	if ((udev->speed >= USB_SPEED_SUPER_PLUS) &&
	    USB_SS_SSP_ISOC_COMP(ep->ss_ep_comp.bmAttributes))
		return le32_to_cpu(ep->ssp_isoc_ep_comp.dwBytesPerInterval);

	else if (udev->speed >= USB_SPEED_SUPER)
		return le16_to_cpu(ep->ss_ep_comp.wBytesPerInterval);

	max_packet = GET_MAX_PACKET(usb_endpoint_maxp(&ep->desc));
	max_burst = (usb_endpoint_maxp(&ep->desc) & 0x1800) >> 11;

	return max_packet * (max_burst + 1);
}
