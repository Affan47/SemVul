if_usb_disconnect(struct usb_interface *intf)
{
	struct if_usb_card *cardp = usb_get_intfdata(intf);
	struct lbs_private *priv = cardp->priv;

	lbs_deb_enter(LBS_DEB_MAIN);

	cardp->surprise_removed = 1;

	if (priv) {
		lbs_stop_card(priv);
		lbs_remove_card(priv);
	}


	if_usb_free(cardp);

	usb_set_intfdata(intf, NULL);
	usb_put_dev(interface_to_usbdev(intf));

	lbs_deb_leave(LBS_DEB_MAIN);
}
