tda10045_init(struct dvb_frontend* fe)
{
	struct tda1004x_state* state = fe->demodulator_priv;

	dprintk("%s\n", __func__);

	if (tda10045_fwupload(fe)) {
		printk("tda1004x: firmware upload failed\n");
		return -EIO;
	}

	tda1004x_write_mask(state, TDA1004X_CONFADC1, 0x10, 0);


	tda1004x_write_mask(state, TDA1004X_CONFC4, 0x20, 0);
	tda1004x_write_mask(state, TDA1004X_AUTO, 8, 0);
	tda1004x_write_mask(state, TDA1004X_CONFC1, 0x40, 0);
	tda1004x_write_mask(state, TDA1004X_CONFC1, 0x80, 0x80);
	tda1004x_write_mask(state, TDA1004X_AUTO, 0x10, 0x10);
	tda1004x_write_mask(state, TDA1004X_IN_CONF2, 0xC0, 0x0);
	tda1004x_write_byteI(state, TDA1004X_CONF_TS1, 0);
	tda1004x_write_byteI(state, TDA1004X_CONF_TS2, 0);
	tda1004x_write_mask(state, TDA1004X_VBER_MSB, 0xe0, 0xa0);
	tda1004x_write_mask(state, TDA1004X_CONFC1, 0x10, 0);
	tda1004x_write_byteI(state, TDA1004X_CONFADC1, 0x2e);

	tda1004x_write_mask(state, 0x1f, 0x01, state->config->invert_oclk);

	return 0;
}
