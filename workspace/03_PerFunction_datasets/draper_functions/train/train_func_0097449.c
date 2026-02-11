udc_irq(struct ci_hdrc *ci)
{
	irqreturn_t retval;
	u32 intr;

	if (ci == NULL)
		return IRQ_HANDLED;

	spin_lock(&ci->lock);

	if (ci->platdata->flags & CI_HDRC_REGS_SHARED) {
		if (hw_read(ci, OP_USBMODE, USBMODE_CM) !=
				USBMODE_CM_DC) {
			spin_unlock(&ci->lock);
			return IRQ_NONE;
		}
	}
	intr = hw_test_and_clear_intr_active(ci);

	if (intr) {

		if (USBi_URI & intr)
			isr_reset_handler(ci);

		if (USBi_PCI & intr) {
			ci->gadget.speed = hw_port_is_high_speed(ci) ?
				USB_SPEED_HIGH : USB_SPEED_FULL;
			if (ci->suspended && ci->driver->resume) {
				spin_unlock(&ci->lock);
				ci->driver->resume(&ci->gadget);
				spin_lock(&ci->lock);
				ci->suspended = 0;
			}
		}

		if (USBi_UI  & intr)
			isr_tr_complete_handler(ci);

		if (USBi_SLI & intr) {
			if (ci->gadget.speed != USB_SPEED_UNKNOWN &&
			    ci->driver->suspend) {
				ci->suspended = 1;
				spin_unlock(&ci->lock);
				ci->driver->suspend(&ci->gadget);
				usb_gadget_set_state(&ci->gadget,
						USB_STATE_SUSPENDED);
				spin_lock(&ci->lock);
			}
		}
		retval = IRQ_HANDLED;
	} else {
		retval = IRQ_NONE;
	}
	spin_unlock(&ci->lock);

	return retval;
}
