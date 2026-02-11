isp1760_udc_reset(struct isp1760_udc *udc)
{
	unsigned long flags;

	spin_lock_irqsave(&udc->lock, flags);


	isp1760_udc_init_hw(udc);

	udc->ep0_state = ISP1760_CTRL_SETUP;
	udc->gadget.speed = USB_SPEED_FULL;

	usb_gadget_udc_reset(&udc->gadget, udc->driver);

	spin_unlock_irqrestore(&udc->lock, flags);
}
