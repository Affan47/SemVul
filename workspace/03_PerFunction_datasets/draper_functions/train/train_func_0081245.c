dib0090_register(struct dvb_frontend *fe, struct i2c_adapter *i2c, const struct dib0090_config *config)
{
	struct dib0090_state *st = kzalloc(sizeof(struct dib0090_state), GFP_KERNEL);
	if (st == NULL)
		return NULL;

	st->config = config;
	st->i2c = i2c;
	st->fe = fe;
	mutex_init(&st->i2c_buffer_lock);
	fe->tuner_priv = st;

	if (config->wbd == NULL)
		st->current_wbd_table = dib0090_wbd_table_default;
	else
		st->current_wbd_table = config->wbd;

	if (dib0090_reset(fe) != 0)
		goto free_mem;

	printk(KERN_INFO "DiB0090: successfully identified\n");
	memcpy(&fe->ops.tuner_ops, &dib0090_ops, sizeof(struct dvb_tuner_ops));

	return fe;
 free_mem:
	kfree(st);
	fe->tuner_priv = NULL;
	return NULL;
}
