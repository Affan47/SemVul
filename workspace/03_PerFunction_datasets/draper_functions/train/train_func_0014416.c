DCD_EP_Open(USB_OTG_CORE_HANDLE *pdev ,
					 uint8_t ep_addr,
					 uint16_t ep_mps,
					 uint8_t ep_type) {
	USB_OTG_EP *ep;

	if ((ep_addr & 0x80) == 0x80) {
		ep = &pdev->dev.in_ep[ep_addr & 0x7F];
	} else {
		ep = &pdev->dev.out_ep[ep_addr & 0x7F];
	}
	ep->num   = ep_addr & 0x7F;

	ep->is_in = (0x80 & ep_addr) != 0;
	ep->maxpacket = ep_mps;
	ep->type = ep_type;
	if (ep->is_in) {

		ep->tx_fifo_num = ep->num;
	}

	if (ep_type == USB_OTG_EP_BULK ) {
		ep->data_pid_start = 0;
	}
	USB_OTG_EPActivate(pdev , ep );
	return 0;
}
