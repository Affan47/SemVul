max2165_attach(struct dvb_frontend *fe,
				   struct i2c_adapter *i2c,
				   struct max2165_config *cfg)
{
	struct max2165_priv *priv = NULL;

	dprintk("%s(%d-%04x)\n", __func__,
		i2c ? i2c_adapter_id(i2c) : -1,
		cfg ? cfg->i2c_address : -1);

	priv = kzalloc(sizeof(struct max2165_priv), GFP_KERNEL);
	if (priv == NULL)
		return NULL;

	memcpy(&fe->ops.tuner_ops, &max2165_tuner_ops,
		sizeof(struct dvb_tuner_ops));

	priv->config = cfg;
	priv->i2c = i2c;
	fe->tuner_priv = priv;

	max2165_init(fe);
	max2165_debug_status(priv);

	return fe;
}
