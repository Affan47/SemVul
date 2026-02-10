lme2510_pid_filter_ctrl(struct dvb_usb_adapter *adap, int onoff)
{
	struct dvb_usb_device *d = adap_to_d(adap);
	struct lme2510_state *st = adap_to_priv(adap);
	static u8 clear_pid_reg[] = LME_ALL_PIDS;
	static u8 rbuf[1];
	int ret = 0;

	deb_info(1, "PID Clearing Filter");

	mutex_lock(&d->i2c_mutex);

	if (!onoff) {
		ret |= lme2510_usb_talk(d, clear_pid_reg,
			sizeof(clear_pid_reg), rbuf, sizeof(rbuf));
		st->pid_off = true;
	} else
		st->pid_off = false;

	st->pid_size = 0;

	mutex_unlock(&d->i2c_mutex);

	return 0;
}
