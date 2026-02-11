sisusbcon_cursor(struct vc_data *c, int mode)
{
	struct sisusb_usb_data *sisusb;
	int from, to, baseline;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	if (!sisusb)
		return;


	if (sisusb_is_inactive(c, sisusb)) {
		mutex_unlock(&sisusb->lock);
		return;
	}

	if (c->vc_origin != c->vc_visible_origin) {
		c->vc_visible_origin = c->vc_origin;
		sisusbcon_set_start_address(sisusb, c);
	}

	if (mode == CM_ERASE) {
		sisusb_setidxregor(sisusb, SISCR, 0x0a, 0x20);
		sisusb->sisusb_cursor_size_to = -1;
		mutex_unlock(&sisusb->lock);
		return;
	}

	sisusb_set_cursor(sisusb, (c->vc_pos - sisusb->scrbuf) / 2);

	baseline = c->vc_font.height - (c->vc_font.height < 10 ? 1 : 2);

	switch (c->vc_cursor_type & 0x0f) {
		case CUR_BLOCK:		from = 1;
					to   = c->vc_font.height;
					break;
		case CUR_TWO_THIRDS:	from = c->vc_font.height / 3;
					to   = baseline;
					break;
		case CUR_LOWER_HALF:	from = c->vc_font.height / 2;
					to   = baseline;
					break;
		case CUR_LOWER_THIRD:	from = (c->vc_font.height * 2) / 3;
					to   = baseline;
					break;
		case CUR_NONE:		from = 31;
					to = 30;
					break;
		default:
		case CUR_UNDERLINE:	from = baseline - 1;
					to   = baseline;
					break;
	}

	if (sisusb->sisusb_cursor_size_from != from ||
	    sisusb->sisusb_cursor_size_to != to) {

		sisusb_setidxreg(sisusb, SISCR, 0x0a, from);
		sisusb_setidxregandor(sisusb, SISCR, 0x0b, 0xe0, to);

		sisusb->sisusb_cursor_size_from = from;
		sisusb->sisusb_cursor_size_to   = to;
	}

	mutex_unlock(&sisusb->lock);
}
