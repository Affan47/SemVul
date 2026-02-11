ds3000_diseqc_send_burst(struct dvb_frontend *fe,
				    enum fe_sec_mini_cmd burst)
{
	struct ds3000_state *state = fe->demodulator_priv;
	int i;
	u8 data;

	dprintk("%s()\n", __func__);

	data = ds3000_readreg(state, 0xa2);
	data &= ~0xc0;
	ds3000_writereg(state, 0xa2, data);


	if (burst == SEC_MINI_A)

		ds3000_writereg(state, 0xa1, 0x02);
	else if (burst == SEC_MINI_B)

		ds3000_writereg(state, 0xa1, 0x01);
	else
		return -EINVAL;

	msleep(13);
	for (i = 0; i < 5; i++) {
		data = ds3000_readreg(state, 0xa1);
		if ((data & 0x40) == 0)
			break;
		msleep(1);
	}

	if (i == 5) {
		data = ds3000_readreg(state, 0xa1);
		data &= ~0x80;
		data |= 0x40;
		ds3000_writereg(state, 0xa1, data);

		data = ds3000_readreg(state, 0xa2);
		data &= ~0xc0;
		data |= 0x80;
		ds3000_writereg(state, 0xa2, data);

		return 1;
	}

	data = ds3000_readreg(state, 0xa2);
	data &= ~0xc0;
	data |= 0x80;
	ds3000_writereg(state, 0xa2, data);

	return 0;
}
