ch9setaddress(struct mv_udc *udc, struct usb_ctrlrequest *setup)
{
	udc->dev_addr = (u8)setup->wValue;


	udc->usb_state = USB_STATE_ADDRESS;

	if (udc_prime_status(udc, EP_DIR_IN, 0, true))
		ep0_stall(udc);
}
