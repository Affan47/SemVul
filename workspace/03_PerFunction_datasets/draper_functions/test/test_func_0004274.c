t3_mdio_change_bits(struct cphy *phy, int mmd, int reg, unsigned int clear,
			unsigned int set)
{
	int ret;
	unsigned int val;

	ret = t3_mdio_read(phy, mmd, reg, &val);
	if (!ret) {
		val &= ~clear;
		ret = t3_mdio_write(phy, mmd, reg, val | set);
	}
	return ret;
}
