mt7601u_bbp_rmc(struct mt7601u_dev *dev, u8 offset, u8 mask, u8 val)
{
	int ret;

	ret = mt7601u_bbp_rr(dev, offset);
	if (ret < 0)
		return ret;
	val |= ret & ~mask;
	if (ret != val)
		mt7601u_bbp_wr(dev, offset, val);

	return val;
}
