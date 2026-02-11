sisusbcon_set_origin(struct vc_data *c)
{
	struct sisusb_usb_data *sisusb;


	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	if (!sisusb)
		return 0;


	if (sisusb_is_inactive(c, sisusb) || sisusb->con_blanked) {
		mutex_unlock(&sisusb->lock);
		return 0;
	}

	c->vc_origin = c->vc_visible_origin = sisusb->scrbuf;

	sisusbcon_set_start_address(sisusb, c);

	sisusb->con_rolled_over = 0;

	mutex_unlock(&sisusb->lock);

	return 1;
}
