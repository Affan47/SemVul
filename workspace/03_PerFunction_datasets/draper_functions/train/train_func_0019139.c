samsung_dtos403ih102a_set(struct dvb_frontend *fe, u8 *buf)
{
	struct dvb_pll_priv *priv = fe->tuner_priv;
	struct i2c_msg msg = {
		.addr = priv->pll_i2c_address,
		.flags = 0,
		.buf = buf,
		.len = 4
	};
	int result;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	result = i2c_transfer(priv->i2c, &msg, 1);
	if (result != 1)
		printk(KERN_ERR "%s: i2c_transfer failed:%d",
			__func__, result);

	buf[2] = 0x9e;
	buf[3] = 0x90;

	return;
}
