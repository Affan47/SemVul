tda827x_probe_version(struct dvb_frontend *fe)
{
	u8 data;
	int rc;
	struct tda827x_priv *priv = fe->tuner_priv;
	struct i2c_msg msg = { .addr = priv->i2c_addr, .flags = I2C_M_RD,
			       .buf = &data, .len = 1 };

	rc = tuner_transfer(fe, &msg, 1);

	if (rc < 0) {
		printk("%s: could not read from tuner at addr: 0x%02x\n",
		       __func__, msg.addr << 1);
		return rc;
	}
	if ((data & 0x3c) == 0) {
		dprintk("tda827x tuner found\n");
		fe->ops.tuner_ops.init  = tda827x_init;
		fe->ops.tuner_ops.sleep = tda827xo_sleep;
		if (priv->cfg)
			priv->cfg->agcf = tda827xo_agcf;
	} else {
		dprintk("tda827xa tuner found\n");
		memcpy(&fe->ops.tuner_ops, &tda827xa_tuner_ops, sizeof(struct dvb_tuner_ops));
		if (priv->cfg)
			priv->cfg->agcf = tda827xa_agcf;
	}
	return 0;
}
