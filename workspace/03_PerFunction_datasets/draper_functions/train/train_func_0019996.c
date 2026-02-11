b43_httab_write(struct b43_wldev *dev, u32 offset, u32 value)
{
	u32 type;

	type = offset & B43_HTTAB_TYPEMASK;
	offset &= 0xFFFF;

	switch (type) {
	case B43_HTTAB_8BIT:
		B43_WARN_ON(value & ~0xFF);
		b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, offset);
		b43_phy_write(dev, B43_PHY_HT_TABLE_DATALO, value);
		break;
	case B43_HTTAB_16BIT:
		B43_WARN_ON(value & ~0xFFFF);
		b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, offset);
		b43_phy_write(dev, B43_PHY_HT_TABLE_DATALO, value);
		break;
	case B43_HTTAB_32BIT:
		b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, offset);
		b43_phy_write(dev, B43_PHY_HT_TABLE_DATAHI, value >> 16);
		b43_phy_write(dev, B43_PHY_HT_TABLE_DATALO, value & 0xFFFF);
		break;
	default:
		B43_WARN_ON(1);
	}

	return;
}
