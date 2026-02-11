cxd2841er_read_regs(struct cxd2841er_priv *priv,
			       u8 addr, u8 reg, u8 *val, u32 len)
{
	int ret;
	u8 i2c_addr = (addr == I2C_SLVX ?
		priv->i2c_addr_slvx : priv->i2c_addr_slvt);
	struct i2c_msg msg[2] = {
		{
			.addr = i2c_addr,
			.flags = 0,
			.len = 1,
			.buf = &reg,
		}, {
			.addr = i2c_addr,
			.flags = I2C_M_RD,
			.len = len,
			.buf = val,
		}
	};

	ret = i2c_transfer(priv->i2c, &msg[0], 1);
	if (ret >= 0 && ret != 1)
		ret = -EIO;
	if (ret < 0) {
		dev_warn(&priv->i2c->dev,
			"%s: i2c rw failed=%d addr=%02x reg=%02x\n",
			KBUILD_MODNAME, ret, i2c_addr, reg);
		return ret;
	}
	ret = i2c_transfer(priv->i2c, &msg[1], 1);
	if (ret >= 0 && ret != 1)
		ret = -EIO;
	if (ret < 0) {
		dev_warn(&priv->i2c->dev,
			"%s: i2c rd failed=%d addr=%02x reg=%02x\n",
			KBUILD_MODNAME, ret, i2c_addr, reg);
		return ret;
	}
	return 0;
}
