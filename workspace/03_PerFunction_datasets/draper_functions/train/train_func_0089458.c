dib8000_release(struct dvb_frontend *fe)
{
	struct dib8000_state *st = fe->demodulator_priv;
	u8 index_frontend;

	for (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (st->fe[index_frontend] != NULL); index_frontend++)
		dvb_frontend_detach(st->fe[index_frontend]);

	dibx000_exit_i2c_master(&st->i2c_master);
	i2c_del_adapter(&st->dib8096p_tuner_adap);
	kfree(st->fe[0]);
	kfree(st);
}
