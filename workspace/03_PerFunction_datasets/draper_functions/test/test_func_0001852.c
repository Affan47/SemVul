carl9170_usb_submit_rx_urb(struct ar9170 *ar, gfp_t gfp)
{
	struct urb *urb;
	int err = 0, runs = 0;

	while ((atomic_read(&ar->rx_anch_urbs) < AR9170_NUM_RX_URBS) &&
		(runs++ < AR9170_NUM_RX_URBS)) {
		err = -ENOSPC;
		urb = usb_get_from_anchor(&ar->rx_pool);
		if (urb) {
			usb_anchor_urb(urb, &ar->rx_anch);
			err = usb_submit_urb(urb, gfp);
			if (unlikely(err)) {
				usb_unanchor_urb(urb);
				usb_anchor_urb(urb, &ar->rx_pool);
			} else {
				atomic_dec(&ar->rx_pool_urbs);
				atomic_inc(&ar->rx_anch_urbs);
			}
			usb_free_urb(urb);
		}
	}

	return err;
}
