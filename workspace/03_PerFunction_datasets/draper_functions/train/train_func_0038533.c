dib7000m_attach(struct i2c_adapter *i2c_adap, u8 i2c_addr, struct dib7000m_config *cfg)
{
	struct dvb_frontend *demod;
	struct dib7000m_state *st;
	st = kzalloc(sizeof(struct dib7000m_state), GFP_KERNEL);
	if (st == NULL)
		return NULL;

	memcpy(&st->cfg, cfg, sizeof(struct dib7000m_config));
	st->i2c_adap = i2c_adap;
	st->i2c_addr = i2c_addr;

	demod                   = &st->demod;
	demod->demodulator_priv = st;
	memcpy(&st->demod.ops, &dib7000m_ops, sizeof(struct dvb_frontend_ops));
	mutex_init(&st->i2c_buffer_lock);

	st->timf_default = cfg->bw->timf;

	if (dib7000m_identify(st) != 0)
		goto error;

	if (st->revision == 0x4000)
		dibx000_init_i2c_master(&st->i2c_master, DIB7000, st->i2c_adap, st->i2c_addr);
	else
		dibx000_init_i2c_master(&st->i2c_master, DIB7000MC, st->i2c_adap, st->i2c_addr);

	dib7000m_demod_reset(st);

	return demod;

error:
	kfree(st);
	return NULL;
}
