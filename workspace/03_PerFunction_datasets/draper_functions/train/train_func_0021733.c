cxd2841er_set_reg_bits(struct cxd2841er_priv *priv,
				  u8 addr, u8 reg, u8 data, u8 mask)
{
	int res;
	u8 rdata;

	if (mask != 0xff) {
		res = cxd2841er_read_reg(priv, addr, reg, &rdata);
		if (res)
			return res;
		data = ((data & mask) | (rdata & (mask ^ 0xFF)));
	}
	return cxd2841er_write_reg(priv, addr, reg, data);
}
