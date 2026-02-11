tuner_transfer(struct dvb_frontend *fe,
			  struct i2c_msg *msg,
			  const int size)
{
	int rc;
	struct tda827x_priv *priv = fe->tuner_priv;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	rc = i2c_transfer(priv->i2c_adap, msg, size);
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	if (rc >= 0 && rc != size)
		return -EIO;

	return rc;
}
