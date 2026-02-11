mv_udc_stop(struct usb_gadget *gadget)
{
	struct mv_udc *udc;
	unsigned long flags;

	udc = container_of(gadget, struct mv_udc, gadget);

	spin_lock_irqsave(&udc->lock, flags);

	mv_udc_enable(udc);
	udc_stop(udc);


	udc->gadget.speed = USB_SPEED_UNKNOWN;
	stop_activity(udc, NULL);
	mv_udc_disable(udc);

	spin_unlock_irqrestore(&udc->lock, flags);


	udc->driver = NULL;

	return 0;
}
