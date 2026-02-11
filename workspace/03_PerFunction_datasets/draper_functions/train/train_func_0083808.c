gp8psk_fe_update_status(struct gp8psk_fe_state *st)
{
	u8 buf[6];
	if (time_after(jiffies,st->next_status_check)) {
		gp8psk_usb_in_op(st->d, GET_SIGNAL_LOCK, 0,0,&st->lock,1);
		gp8psk_usb_in_op(st->d, GET_SIGNAL_STRENGTH, 0,0,buf,6);
		st->snr = (buf[1]) << 8 | buf[0];
		st->next_status_check = jiffies + (st->status_check_interval*HZ)/1000;
	}
	return 0;
}
