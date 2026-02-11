handle_regs_int_override(struct urb *urb)
{
	struct zd_usb *usb = urb->context;
	struct zd_usb_interrupt *intr = &usb->intr;

	spin_lock(&intr->lock);
	if (atomic_read(&intr->read_regs_enabled)) {
		atomic_set(&intr->read_regs_enabled, 0);
		intr->read_regs_int_overridden = 1;
		complete(&intr->read_regs.completion);
	}
	spin_unlock(&intr->lock);
}
