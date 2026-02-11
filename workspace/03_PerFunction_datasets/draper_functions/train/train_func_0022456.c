digitv_rc_query(struct dvb_usb_device *d, u32 *event, int *state)
{
	int i;
	u8 key[5];
	u8 b[4] = { 0 };

	*event = 0;
	*state = REMOTE_NO_KEY_PRESSED;

	digitv_ctrl_msg(d,USB_READ_REMOTE,0,NULL,0,&key[1],4);


	digitv_ctrl_msg(d,USB_WRITE_REMOTE,0,b,4,NULL,0);


	if (key[1] != 0)
	{
		  for (i = 0; i < d->props.rc.legacy.rc_map_size; i++) {
			if (rc5_custom(&d->props.rc.legacy.rc_map_table[i]) == key[1] &&
			    rc5_data(&d->props.rc.legacy.rc_map_table[i]) == key[2]) {
				*event = d->props.rc.legacy.rc_map_table[i].keycode;
				*state = REMOTE_KEY_PRESSED;
				return 0;
			}
		}
	}

	if (key[0] != 0)
		deb_rc("key: %*ph\n", 5, key);
	return 0;
}
