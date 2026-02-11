tda1004x_read_ucblocks(struct dvb_frontend* fe, u32* ucblocks)
{
	struct tda1004x_state* state = fe->demodulator_priv;
	int tmp;
	int tmp2;
	int counter;

	dprintk("%s\n", __func__);


	counter = 0;
	tmp = tda1004x_read_byte(state, TDA1004X_UNCOR);
	if (tmp < 0)
		return -EIO;
	tmp &= 0x7f;
	while (counter++ < 5) {
		tda1004x_write_mask(state, TDA1004X_UNCOR, 0x80, 0);
		tda1004x_write_mask(state, TDA1004X_UNCOR, 0x80, 0);
		tda1004x_write_mask(state, TDA1004X_UNCOR, 0x80, 0);

		tmp2 = tda1004x_read_byte(state, TDA1004X_UNCOR);
		if (tmp2 < 0)
			return -EIO;
		tmp2 &= 0x7f;
		if ((tmp2 < tmp) || (tmp2 == 0))
			break;
	}

	if (tmp != 0x7f)
		*ucblocks = tmp;
	else
		*ucblocks = 0xffffffff;

	dprintk("%s: ucblocks=0x%x\n", __func__, *ucblocks);
	return 0;
}
