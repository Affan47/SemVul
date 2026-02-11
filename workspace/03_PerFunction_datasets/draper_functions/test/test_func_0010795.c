dtt200u_fe_set_frontend(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *fep = &fe->dtv_property_cache;
	struct dtt200u_fe_state *state = fe->demodulator_priv;
	int i;
	enum fe_status st;
	u16 freq = fep->frequency / 250000;
	u8 bwbuf[2] = { SET_BANDWIDTH, 0 },freqbuf[3] = { SET_RF_FREQ, 0, 0 };

	switch (fep->bandwidth_hz) {
	case 8000000:
		bwbuf[1] = 8;
		break;
	case 7000000:
		bwbuf[1] = 7;
		break;
	case 6000000:
		bwbuf[1] = 6;
		break;
	default:
		return -EINVAL;
	}

	dvb_usb_generic_write(state->d,bwbuf,2);

	freqbuf[1] = freq & 0xff;
	freqbuf[2] = (freq >> 8) & 0xff;
	dvb_usb_generic_write(state->d,freqbuf,3);

	for (i = 0; i < 30; i++) {
		msleep(20);
		dtt200u_fe_read_status(fe, &st);
		if (st & FE_TIMEDOUT)
			continue;
	}

	return 0;
}
