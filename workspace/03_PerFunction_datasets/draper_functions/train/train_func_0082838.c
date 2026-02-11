ci_udc_wakeup(struct usb_gadget *_gadget)
{
	struct ci_hdrc *ci = container_of(_gadget, struct ci_hdrc, gadget);
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&ci->lock, flags);
	if (!ci->remote_wakeup) {
		ret = -EOPNOTSUPP;
		goto out;
	}
	if (!hw_read(ci, OP_PORTSC, PORTSC_SUSP)) {
		ret = -EINVAL;
		goto out;
	}
	hw_write(ci, OP_PORTSC, PORTSC_FPR, PORTSC_FPR);
out:
	spin_unlock_irqrestore(&ci->lock, flags);
	return ret;
}
