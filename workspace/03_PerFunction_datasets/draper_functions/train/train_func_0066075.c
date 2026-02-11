b43_nphy_pa_set_tx_dig_filter(struct b43_wldev *dev, u16 offset,
					  const s16 *filter)
{
	int i;

	offset = B43_PHY_N(offset);

	for (i = 0; i < 15; i++, offset++)
		b43_phy_write(dev, offset, filter[i]);
}
