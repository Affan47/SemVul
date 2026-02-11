sisusb_is_inactive(struct vc_data *c, struct sisusb_usb_data *sisusb)
{
	if (sisusb->is_gfx ||
	    sisusb->textmodedestroyed ||
	    c->vc_mode != KD_TEXT)
		return 1;

	return 0;
}
