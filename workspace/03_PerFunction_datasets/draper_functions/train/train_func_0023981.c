r8a66597_stop(struct usb_gadget *gadget)
{
	struct r8a66597 *r8a66597 = gadget_to_r8a66597(gadget);
	unsigned long flags;

	spin_lock_irqsave(&r8a66597->lock, flags);
	r8a66597_bclr(r8a66597, VBSE, INTENB0);
	disable_controller(r8a66597);
	spin_unlock_irqrestore(&r8a66597->lock, flags);

	r8a66597->driver = NULL;
	return 0;
}
