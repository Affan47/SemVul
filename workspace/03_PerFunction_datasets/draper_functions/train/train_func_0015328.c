cxd2841er_read_status_t_t2(struct cxd2841er_priv *priv,
				      u8 *sync, u8 *tslock, u8 *unlock)
{
	u8 data = 0;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	if (priv->state != STATE_ACTIVE_TC)
		return -EINVAL;
	if (priv->system == SYS_DVBT) {

		cxd2841er_write_reg(priv, I2C_SLVT, 0x00, 0x10);
	} else {

		cxd2841er_write_reg(priv, I2C_SLVT, 0x00, 0x20);
	}
	cxd2841er_read_reg(priv, I2C_SLVT, 0x10, &data);
	if ((data & 0x07) == 0x07) {
		dev_dbg(&priv->i2c->dev,
			"%s(): invalid hardware state detected\n", __func__);
		*sync = 0;
		*tslock = 0;
		*unlock = 0;
	} else {
		*sync = ((data & 0x07) == 0x6 ? 1 : 0);
		*tslock = ((data & 0x20) ? 1 : 0);
		*unlock = ((data & 0x10) ? 1 : 0);
	}
	return 0;
}
