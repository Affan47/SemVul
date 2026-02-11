dib8090_agc_control(struct dvb_frontend *fe, u8 restart)
{
	deb_info("AGC control callback: %i\n", restart);
	dib0090_dcc_freq(fe, restart);

	if (restart == 0)
		dib0090_set_dc_servo(fe, 1);
}
