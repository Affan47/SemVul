wa_handle_notif_xfer(struct wahc *wa, struct wa_notif_hdr *notif_hdr)
{
	struct device *dev = &wa->usb_iface->dev;
	struct wa_notif_xfer *notif_xfer;
	const struct usb_endpoint_descriptor *dti_epd = wa->dti_epd;

	notif_xfer = container_of(notif_hdr, struct wa_notif_xfer, hdr);
	BUG_ON(notif_hdr->bNotifyType != WA_NOTIF_TRANSFER);

	if ((0x80 | notif_xfer->bEndpoint) != dti_epd->bEndpointAddress) {

		dev_err(dev, "BUG: DTI ep is %u, not %u (hack me)\n",
			notif_xfer->bEndpoint, dti_epd->bEndpointAddress);
		goto error;
	}


	if (wa_dti_start(wa) < 0)
		goto error;

	return;

error:
	wa_reset_all(wa);
}
