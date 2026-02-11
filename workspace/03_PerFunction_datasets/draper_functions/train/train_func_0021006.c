nfcmrvl_play_deferred(struct nfcmrvl_usb_drv_data *drv_data)
{
	struct urb *urb;
	int err;

	while ((urb = usb_get_from_anchor(&drv_data->deferred))) {
		err = usb_submit_urb(urb, GFP_ATOMIC);
		if (err)
			break;

		drv_data->tx_in_flight++;
	}
	usb_scuttle_anchored_urbs(&drv_data->deferred);
}
