fotg210_set_address(struct fotg210_udc *fotg210,
				struct usb_ctrlrequest *ctrl)
{
	if (ctrl->wValue >= 0x0100) {
		fotg210_request_error(fotg210);
	} else {
		fotg210_set_dev_addr(fotg210, ctrl->wValue);
		fotg210_set_cxdone(fotg210);
	}
}
