mt7601u_rf_rmw(struct mt7601u_dev *dev, u8 bank, u8 offset, u8 mask, u8 val)
{
	int ret;

	ret = mt7601u_rf_rr(dev, bank, offset);
	if (ret < 0)
		return ret;
	val |= ret & ~mask;
	ret = mt7601u_rf_wr(dev, bank, offset, val);
	if (ret)
		return ret;

	return val;
}
