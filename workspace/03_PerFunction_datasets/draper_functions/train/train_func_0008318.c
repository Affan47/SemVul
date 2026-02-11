usb_hcd_poll_rh_status(struct usb_hcd *hcd)
{
	struct urb	*urb;
	int		length;
	unsigned long	flags;
	char		buffer[6];

	if (unlikely(!hcd->rh_pollable))
		return;
	if (!hcd->uses_new_polling && !hcd->status_urb)
		return;

	length = hcd->driver->hub_status_data(hcd, buffer);
	if (length > 0) {


		spin_lock_irqsave(&hcd_root_hub_lock, flags);
		urb = hcd->status_urb;
		if (urb) {
			clear_bit(HCD_FLAG_POLL_PENDING, &hcd->flags);
			hcd->status_urb = NULL;
			urb->actual_length = length;
			memcpy(urb->transfer_buffer, buffer, length);

			usb_hcd_unlink_urb_from_ep(hcd, urb);
			usb_hcd_giveback_urb(hcd, urb, 0);
		} else {
			length = 0;
			set_bit(HCD_FLAG_POLL_PENDING, &hcd->flags);
		}
		spin_unlock_irqrestore(&hcd_root_hub_lock, flags);
	}


	if (hcd->uses_new_polling ? HCD_POLL_RH(hcd) :
			(length == 0 && hcd->status_urb != NULL))
		mod_timer (&hcd->rh_timer, (jiffies/(HZ/4) + 1) * (HZ/4));
}
