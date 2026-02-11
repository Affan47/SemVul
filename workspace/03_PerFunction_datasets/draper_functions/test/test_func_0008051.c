lme2510_streaming_ctrl(struct dvb_frontend *fe, int onoff)
{
	struct dvb_usb_adapter *adap = fe_to_adap(fe);
	struct dvb_usb_device *d = adap_to_d(adap);
	struct lme2510_state *st = adap_to_priv(adap);
	static u8 clear_reg_3[] = LME_ALL_PIDS;
	static u8 rbuf[1];
	int ret = 0, rlen = sizeof(rbuf);

	deb_info(1, "STM  (%02x)", onoff);


	if (onoff == 1)
		st->stream_on = 1;
	else {
		deb_info(1, "STM Steam Off");

		mutex_lock(&d->i2c_mutex);

		ret = lme2510_usb_talk(d, clear_reg_3,
				sizeof(clear_reg_3), rbuf, rlen);
		st->stream_on = 0;
		st->i2c_talk_onoff = 1;

		mutex_unlock(&d->i2c_mutex);
	}

	return (ret < 0) ? -ENODEV : 0;
}
