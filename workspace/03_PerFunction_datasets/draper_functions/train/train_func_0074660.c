r8a66597_hub_status_data(struct usb_hcd *hcd, char *buf)
{
	struct r8a66597 *r8a66597 = hcd_to_r8a66597(hcd);
	unsigned long flags;
	int i;

	r8a66597_check_detect_child(r8a66597, hcd);

	spin_lock_irqsave(&r8a66597->lock, flags);

	*buf = 0;

	for (i = 0; i < r8a66597->max_root_hub; i++) {
		if (r8a66597->root_hub[i].port & 0xffff0000)
			*buf |= 1 << (i + 1);
	}

	spin_unlock_irqrestore(&r8a66597->lock, flags);

	return (*buf != 0);
}
