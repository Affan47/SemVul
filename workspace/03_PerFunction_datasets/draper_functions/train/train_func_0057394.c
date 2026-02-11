ds3000_send_diseqc_msg(struct dvb_frontend *fe,
				struct dvb_diseqc_master_cmd *d)
{
	struct ds3000_state *state = fe->demodulator_priv;
	int i;
	u8 data;


	dprintk("%s(", __func__);
	for (i = 0 ; i < d->msg_len;) {
		dprintk("0x%02x", d->msg[i]);
		if (++i < d->msg_len)
			dprintk(", ");
	}


	data = ds3000_readreg(state, 0xa2);
	data &= ~0xc0;
	ds3000_writereg(state, 0xa2, data);


	for (i = 0; i < d->msg_len; i++)
		ds3000_writereg(state, 0xa3 + i, d->msg[i]);

	data = ds3000_readreg(state, 0xa1);


	data &= ~0xf8;


	data |= ((d->msg_len - 1) << 3) | 0x07;
	ds3000_writereg(state, 0xa1, data);


	for (i = 0; i < 15; i++) {
		data = ds3000_readreg(state, 0xa1);
		if ((data & 0x40) == 0)
			break;
		msleep(10);
	}


	if (i == 15) {
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
