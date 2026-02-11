tda18218_init(struct dvb_frontend *fe)
{
	struct tda18218_priv *priv = fe->tuner_priv;
	int ret;


	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	ret = tda18218_wr_regs(priv, R00_ID, priv->regs, TDA18218_NUM_REGS);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	if (ret)
		dev_dbg(&priv->i2c->dev, "%s: failed=%d\n", __func__, ret);

	return ret;
}
