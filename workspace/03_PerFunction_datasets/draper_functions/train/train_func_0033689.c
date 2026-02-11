ci_udc_vbus_session(struct usb_gadget *_gadget, int is_active)
{
	struct ci_hdrc *ci = container_of(_gadget, struct ci_hdrc, gadget);
	unsigned long flags;
	int gadget_ready = 0;

	spin_lock_irqsave(&ci->lock, flags);
	ci->vbus_active = is_active;
	if (ci->driver)
		gadget_ready = 1;
	spin_unlock_irqrestore(&ci->lock, flags);

	if (gadget_ready) {
		if (is_active) {
			pm_runtime_get_sync(&_gadget->dev);
			hw_device_reset(ci);
			hw_device_state(ci, ci->ep0out->qh.dma);
			usb_gadget_set_state(_gadget, USB_STATE_POWERED);
			usb_udc_vbus_handler(_gadget, true);
		} else {
			usb_udc_vbus_handler(_gadget, false);
			if (ci->driver)
				ci->driver->disconnect(&ci->gadget);
			hw_device_state(ci, 0);
			if (ci->platdata->notify_event)
				ci->platdata->notify_event(ci,
				CI_HDRC_CONTROLLER_STOPPED_EVENT);
			_gadget_stop_activity(&ci->gadget);
			pm_runtime_put_sync(&_gadget->dev);
			usb_gadget_set_state(_gadget, USB_STATE_NOTATTACHED);
		}
	}

	return 0;
}
