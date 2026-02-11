have_ed_get_response(struct usb_ftdi *ftdi,
				  struct u132_target *target, u16 ed_length, int ed_number, int ed_type,
				  char *b)
{
	mutex_lock(&ftdi->u132_lock);
	target->condition_code = TD_DEVNOTRESP;
	target->actual = (ed_length >> 0) & 0x01FF;
	target->non_null = (ed_length >> 15) & 0x0001;
	target->repeat_number = (ed_length >> 11) & 0x000F;
	mutex_unlock(&ftdi->u132_lock);
	if (target->active)
		ftdi_elan_do_callback(ftdi, target, NULL, 0);
	target->abandoning = 0;
	ftdi->received = 0;
	ftdi->expected = 4;
	ftdi->ed_found = 0;
	return ftdi->response;
}
